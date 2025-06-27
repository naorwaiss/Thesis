import gymnasium as gym  # <-- use gymnasium (recommended by SB3)
from stable_baselines3 import TD3
from stable_baselines3.common.noise import NormalActionNoise
import numpy as np

# Create environment
env = gym.make("Pendulum-v1")


# Define action noise (helps exploration in continuous action spaces)
n_actions = env.action_space.shape[0]
action_noise = NormalActionNoise(mean=np.zeros(n_actions), sigma=0.1 * np.ones(n_actions))

# Create TD3 model
model = TD3("MlpPolicy", env, action_noise=action_noise, verbose=1)

# Train the agent
model.learn(total_timesteps=10000)

# Save the model
model.save("td3_pendulum")

# Load and evaluate the agent
model = TD3.load("td3_pendulum")
obs, _ = env.reset()

for _ in range(1000):
    action, _ = model.predict(obs, deterministic=True)
    print(f"Action: {action}")
    obs, reward, terminated, truncated, _ = env.step(action)
    done = terminated or truncated
    env.render()
    if done:
        obs, _ = env.reset()

env.close()
