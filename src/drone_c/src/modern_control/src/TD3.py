import gym
import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
from collections import deque
import copy


def convert_deque_to_torch(deque_data, device='cuda'):

    # Convert deque to list first
    data_list = list(deque_data)
    
    # Check if deque is empty
    if not data_list:
        raise ValueError("Cannot convert empty deque to tensor")
    
    # Convert to numpy array first
    numpy_array = np.array(data_list)
    
    # Convert numpy array to PyTorch tensor
    tensor = torch.from_numpy(numpy_array).float()
    
    # Move tensor to specified device
    tensor = tensor.to(device)
    
    return tensor


class Actor_signal(nn.Module):

    
    def __init__(self, state_dim=2, action_dim=3):
        super(Actor_signal, self).__init__()
        
        # First hidden layer: Maps state to 256-dimensional space
        # Input: state_dim (2) -> Output: 256
        self.fc1 = nn.Linear(state_dim, 256)
        
        # Second hidden layer: Maps 256 to 256 dimensions
        # This allows the network to learn complex non-linear relationships
        self.fc2 = nn.Linear(256, 256)
        
        # Output layer: Maps 256 to action_dim (3)
        # No activation function here to allow continuous action values
        self.fc3 = nn.Linear(256, action_dim)
        
    def forward(self, x):

        # Apply ReLU activation after first layer
        x = torch.relu(self.fc1(x))
        
        # Apply ReLU activation after second layer
        x = torch.relu(self.fc2(x))
        
        # Final layer: no activation for continuous action space
        x = self.fc3(x)
        
        return x


class Critic(nn.Module):

    
    def __init__(self, state_dim, action_dim):
        super().__init__()
        
        self.q1 = nn.Sequential(
            nn.Linear(state_dim + action_dim, 400),  # Concatenated state-action input
            nn.ReLU(),                               # ReLU activation
            nn.Linear(400, 300),                     # Second hidden layer
            nn.ReLU(),                               # ReLU activation
            nn.Linear(300, 1)                        # Output: single Q-value
        )
        
        self.q2 = nn.Sequential(
            nn.Linear(state_dim + action_dim, 400),  # Same input dimension
            nn.ReLU(),                               # Same activation
            nn.Linear(400, 300),                     # Same hidden layer
            nn.ReLU(),                               # Same activation
            nn.Linear(300, 1)                        # Same output dimension
        )

    def forward(self, state, action):
        xu = torch.cat([state, action], 1)
        
        # Return Q-values from both networks
        return self.q1(xu), self.q2(xu)

    def Q1(self, state, action):
        xu = torch.cat([state, action], 1)
        return self.q1(xu)


class TD3:
    def __init__(self, buffer_actual, buffer_desired):
        self.actor = Actor_signal(state_dim=2, action_dim=3).to("cuda")
        self.actor_target = copy.deepcopy(self.actor)
        self.actor_optimizer = optim.Adam(self.actor.parameters(), lr=0.001)

        self.critic = Critic(state_dim=2, action_dim=3).to("cuda")
        self.critic_target = copy.deepcopy(self.critic)
        self.critic_optimizer = optim.Adam(self.critic.parameters(), lr=0.001)

        # Instead of converting deque to tensor once, keep buffers as ReplayBuffer objects
        self.buffer_actual = buffer_actual  # Should be ReplayBuffer instance
        self.buffer_desired = buffer_desired  # Same here or merged, depends on your logic
        
        self.total_it = 0
        self.max_action = 10.0  # Adjust if needed

    def select_action(self, state):
        state = torch.FloatTensor(state.reshape(1, -1)).to("cuda")
        return self.actor(state).cpu().data.numpy().flatten()

    def train(self, batch_size=100, discount=0.99, tau=0.005, policy_noise=0.2, noise_clip=0.5, policy_freq=2):
        # Make sure your replay buffer has enough samples
        if len(self.buffer_actual.buffer) < batch_size:
            return

        self.total_it += 1

        # Sample from your replay buffer (you might want to unify the buffers!)
        state, action, reward, next_state, done = self.buffer_actual.sample(batch_size)

        # Select action according to target policy + clipped noise
        noise = (torch.randn_like(action) * policy_noise).clamp(-noise_clip, noise_clip)
        next_action = (self.actor_target(next_state) + noise).clamp(0, self.max_action)

        # Compute target Q-values
        target_Q1, target_Q2 = self.critic_target(next_state, next_action)
        target_Q = reward + (1 - done) * discount * torch.min(target_Q1, target_Q2)

        # Get current Q estimates
        current_Q1, current_Q2 = self.critic(state, action)

        # Compute critic loss
        critic_loss = nn.MSELoss()(current_Q1, target_Q.detach()) + nn.MSELoss()(current_Q2, target_Q.detach())

        self.critic_optimizer.zero_grad()
        critic_loss.backward()
        self.critic_optimizer.step()

        # Delayed policy updates
        if self.total_it % policy_freq == 0:
            actor_loss = -self.critic.Q1(state, self.actor(state)).mean()

            self.actor_optimizer.zero_grad()
            actor_loss.backward()
            self.actor_optimizer.step()

            # Soft update target networks
            for param, target_param in zip(self.critic.parameters(), self.critic_target.parameters()):
                target_param.data.copy_(tau * param.data + (1 - tau) * target_param.data)

            for param, target_param in zip(self.actor.parameters(), self.actor_target.parameters()):
                target_param.data.copy_(tau * param.data + (1 - tau) * target_param.data) 