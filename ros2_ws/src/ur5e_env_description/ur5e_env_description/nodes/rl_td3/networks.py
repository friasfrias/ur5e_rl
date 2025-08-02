import os
import torch as T
import torch.nn.functional as F
import torch.nn as nn
import torch.optim as optim

# --------------------------
# Critic Network (Q-function)
# --------------------------
class CriticNetwork(nn.Module):
    def __init__(self, input_dims, n_actions, fc1_dims=400, fc2_dims=300,
                 name='critic', chkpt_dir='tmp/td3', learning_rate=1e-3):
        super(CriticNetwork, self).__init__()

        self.input_dims = input_dims  # Expects a tuple, e.g., (4,)
        self.n_actions = n_actions
        self.name = name
        self.checkpoint_dir = chkpt_dir
        self.checkpoint_file = os.path.join(self.checkpoint_dir, name + '_td3')

        # Input is state + action (4 + 2 = 6)
        self.fc1 = nn.Linear(self.input_dims[0] + n_actions, fc1_dims)
        self.fc2 = nn.Linear(fc1_dims, fc2_dims)
        self.q1 = nn.Linear(fc2_dims, 1)  # Output is a scalar Q-value

        self.optimizer = optim.AdamW(self.parameters(), lr=learning_rate, weight_decay=0.005)
        self.device = T.device('cuda:0' if T.cuda.is_available() else 'cpu')
        self.to(self.device)

    def forward(self, state, action):
        # Concatenate state and action along feature dimension
        x = T.cat([state, action], dim=1)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        q = self.q1(x)
        return q

    def save_checkpoint(self):
        T.save(self.state_dict(), self.checkpoint_file)

    def load_checkpoint(self):
        self.load_state_dict(T.load(self.checkpoint_file))


# --------------------------
# Actor Network (Policy)
# --------------------------
class ActorNetwork(nn.Module):
    def __init__(self, input_dims, fc1_dims=400, fc2_dims=300,
                 n_actions=2, name='actor', chkpt_dir='tmp/td3', learning_rate=1e-3):
        super(ActorNetwork, self).__init__()

        self.input_dims = input_dims  # Expects a tuple, e.g., (4,)
        self.n_actions = n_actions
        self.name = name
        self.checkpoint_dir = chkpt_dir
        self.checkpoint_file = os.path.join(self.checkpoint_dir, name + '_td3')

        # Input is only the state
        self.fc1 = nn.Linear(*self.input_dims, fc1_dims)
        self.fc2 = nn.Linear(fc1_dims, fc2_dims)
        self.output = nn.Linear(fc2_dims, self.n_actions)

        self.optimizer = optim.Adam(self.parameters(), lr=learning_rate)
        self.device = T.device('cuda:0' if T.cuda.is_available() else 'cpu')
        self.to(self.device)

    def forward(self, state):
        x = F.relu(self.fc1(state))
        x = F.relu(self.fc2(x))
        # Output is tanh-scaled → later scaled to [min_action, max_action] in Agent
        x = T.tanh(self.output(x))
        return x

    def save_checkpoint(self):
        T.save(self.state_dict(), self.checkpoint_file)

    def load_checkpoint(self):
        self.load_state_dict(T.load(self.checkpoint_file))
