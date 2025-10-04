import torch

class ReplayBuffer:
    def __init__(self, max_size, input_dim, n_actions, device='cpu'):
        self.mem_size = max_size
        self.mem_ctr = 0
        self.device = device

        # Alocação
        self.state_memory      = torch.zeros((max_size, input_dim), dtype=torch.float32, device=device)
        self.new_state_memory  = torch.zeros((max_size, input_dim), dtype=torch.float32, device=device)
        self.action_memory     = torch.zeros((max_size, n_actions), dtype=torch.float32, device=device)
        self.reward_memory     = torch.zeros(max_size, dtype=torch.float32, device=device)

        # Agora guardamos SEPARADO: terminated e truncated (bools)
        self.terminated_memory = torch.zeros(max_size, dtype=torch.bool, device=device)
        self.truncated_memory  = torch.zeros(max_size, dtype=torch.bool, device=device)

        print(f"[ReplayBuffer] Created with capacity {max_size}")
        print(f"[ReplayBuffer] State dim: {input_dim}, Actions: {n_actions}, Device: {device}")

    def store_transition(self, state, action, reward, next_state, terminated, truncated):
        idx = self.mem_ctr % self.mem_size

        self.state_memory[idx]      = torch.as_tensor(state, dtype=torch.float32, device=self.device)
        self.new_state_memory[idx]  = torch.as_tensor(next_state, dtype=torch.float32, device=self.device)
        self.action_memory[idx]     = torch.as_tensor(action, dtype=torch.float32, device=self.device)
        self.reward_memory[idx]     = torch.as_tensor(reward, dtype=torch.float32, device=self.device)
        self.terminated_memory[idx] = torch.as_tensor(terminated, dtype=torch.bool, device=self.device)
        self.truncated_memory[idx]  = torch.as_tensor(truncated, dtype=torch.bool, device=self.device)

        self.mem_ctr += 1

    def sample_buffer(self, batch_size):
        max_mem = min(self.mem_ctr, self.mem_size)
        batch = torch.randint(0, max_mem, (batch_size,), device=self.device)

        states      = self.state_memory[batch]
        actions     = self.action_memory[batch]
        rewards     = self.reward_memory[batch]
        next_states = self.new_state_memory[batch]
        terminateds = self.terminated_memory[batch]
        truncateds  = self.truncated_memory[batch]

        return states, actions, rewards, next_states, terminateds, truncateds

    def __len__(self):
        return min(self.mem_ctr, self.mem_size)
