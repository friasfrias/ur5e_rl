import torch

class ReplayBuffer:
    def __init__(self, max_size, input_dim, n_actions, device='cpu'):
        self.mem_size = max_size
        self.mem_ctr = 0
        self.device = device

        # Allocate memory
        self.state_memory     = torch.zeros((max_size, input_dim), dtype=torch.float32, device=device)
        self.new_state_memory = torch.zeros((max_size, input_dim), dtype=torch.float32, device=device)
        self.action_memory    = torch.zeros((max_size, n_actions), dtype=torch.float32, device=device)
        self.reward_memory    = torch.zeros(max_size, dtype=torch.float32, device=device)
        self.terminal_memory  = torch.zeros(max_size, dtype=torch.bool, device=device)

        print(f"[ReplayBuffer] Created with capacity {max_size}")
        print(f"[ReplayBuffer] State dim: {input_dim}, Actions: {n_actions}, Device: {device}")

    def store_transition(self, state, action, reward, next_state, done):
        index = self.mem_ctr % self.mem_size

        self.state_memory[index]     = torch.tensor(state, dtype=torch.float32, device=self.device)
        self.new_state_memory[index] = torch.tensor(next_state, dtype=torch.float32, device=self.device)
        self.action_memory[index]    = torch.tensor(action, dtype=torch.float32, device=self.device)
        self.reward_memory[index]    = reward
        self.terminal_memory[index]  = done

        self.mem_ctr += 1

    def sample_buffer(self, batch_size):
        max_mem = min(self.mem_ctr, self.mem_size)
        batch = torch.randint(0, max_mem, (batch_size,), device=self.device)

        states     = self.state_memory[batch]
        actions    = self.action_memory[batch]
        rewards    = self.reward_memory[batch]
        next_states = self.new_state_memory[batch]
        dones      = self.terminal_memory[batch]

        return states, actions, rewards, next_states, dones

    def __len__(self):
        return min(self.mem_ctr, self.mem_size)
