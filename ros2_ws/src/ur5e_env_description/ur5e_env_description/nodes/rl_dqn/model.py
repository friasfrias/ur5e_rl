import torch
import torch.nn as nn
import torch.nn.functional as F

class DQNNetwork(nn.Module):  

    """
    Rede neural feedforward para DQN com duas hidden layers.

    Args:
        input_dim (int): dimensão do vetor de estado.
        output_dim (int): número de ações discretas.
        hidden_dim (int): número de nós nas camadas escondidas (default=64).
    """

    def __init__(self, input_dim, output_dim, hidden_dim=128):
        super(DQNNetwork, self).__init__()

        self.fc1 = nn.Linear(input_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, hidden_dim)

        self.output = nn.Linear(hidden_dim, output_dim)

        # Initialize weights
        self.apply(self.weights_init)

    def forward(self, x):

        """
        Propaga x pela rede e retorna tensor de Q-values.
        """

        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))

        output = self.output(x)

        return output


    def weights_init(self, m):
        """
        Inicializa pesos de camadas lineares com Kaiming Normal apropriado para ReLU.
        """
        if isinstance(m, nn.Linear):
            nn.init.kaiming_normal_(m.weight, nonlinearity='relu')
            if m.bias is not None:
                nn.init.constant_(m.bias, 0)


    def save_the_model(self, filename='models/latest.pt'):
        torch.save(self.state_dict(), filename)
    
    def load_the_model(self, filename='models/latest.pt'):
        try:
            self.load_state_dict(torch.load(filename))
            print(f"Loaded weights from {filename}")
        except FileNotFoundError:
            print(f"No weights file found at at {filename}")


def soft_update(target, source, tau=0.005):

    """
    Atualização suave de parâmetros:
    θ_target ← τ·θ_source + (1-τ)·θ_target
    """
    
    for target_param, param in zip(target.parameters(), source.parameters()):
        target_param.data.copy_(target_param.data * (1.0 - tau) + param.data * tau)
