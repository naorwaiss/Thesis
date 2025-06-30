# Research Topics to Study



## Reinforcement Learning with PID Control
- **Adaptive Dynamic Programming**: Understanding how RL can be combined with PID controllers for adaptive control systems
- **Online vs Offline Learning**: Exploring the differences between real-time learning and batch learning approaches

## Deep Reinforcement Learning Algorithms

### Policy-Based Methods
1. **Deep Deterministic Policy Gradient (DDPG)**
   - A model-free, off-policy actor-critic algorithm for continuous action spaces
   
2. **Trust Region Policy Optimization (TRPO)**
   - A policy optimization method that ensures monotonic improvement

3. **Direct Preference Optimization (DPO)**
   - A method for training language models using human preferences

### Value-Based Methods
4. **SARSA (State-Action-Reward-State-Action)**
   - An on-policy temporal difference learning algorithm

5. **Q-Learning**
   - An off-policy temporal difference learning algorithm

6. **Deep Q-Network (DQN)**
   - A deep learning extension of Q-learning using neural networks

## Advanced Techniques

### Twin Delayed Deep Deterministic Policy Gradient (TD3)
- **Description**: An improved version of DDPG that addresses overestimation bias
- **Key Features**:
  - Twin critics to reduce overestimation
  - Delayed policy updates
  - Target policy smoothing regularization

### Polyak Averaging Technique
- **Purpose**: Stabilizing training by maintaining moving averages of network parameters
- **Benefits**: Improves convergence and reduces training instability

---

## Current Progress
- **Reading Status**: Currently on page 5 of the research paper
- **Focus**: Understanding TD3 and its improvements over DDPG