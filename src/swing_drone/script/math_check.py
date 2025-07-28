from sympy import symbols, Matrix, simplify, cos, sin, pprint

print("=== DRONE KINEMATICS ANALYSIS ===\n")

# Define symbols
theta, phi, psi = symbols('theta phi psi')
theta_dot, phi_dot, psi_dot = symbols('theta_dot phi_dot psi_dot')
theta1, theta2, phi1, phi2 = symbols('theta1 theta2 phi1 phi2')
theta1_dot, theta2_dot, phi1_dot, phi2_dot = symbols('theta1_dot theta2_dot phi1_dot phi2_dot')

print("1. INDIVIDUAL ROTATION MATRICES")
print("================================")

# Rotation matrices
R_X = Matrix([
    [1, 0, 0],
    [0, cos(phi), -sin(phi)],
    [0, sin(phi), cos(phi)]
])

R_Y = Matrix([
    [cos(theta), 0, sin(theta)],
    [0, 1, 0],
    [-sin(theta), 0, cos(theta)]
])

R_Z = Matrix([
    [cos(psi), -sin(psi), 0],
    [sin(psi), cos(psi), 0],
    [0, 0, 1]
])

R = R_Z * R_Y * R_X

print("\n3. CALCULATING ANGULAR VELOCITY")
print("================================")

R_dot = R.diff(phi) * phi_dot + R.diff(theta) * theta_dot + R.diff(psi) * psi_dot
S_omega = simplify(R_dot * R.transpose())

omega_x = S_omega[2, 1]
omega_y = S_omega[0, 2]
omega_z = S_omega[1, 0]
omega_inertial = Matrix([omega_x, omega_y, omega_z])
euler_rates = Matrix([phi_dot, theta_dot, psi_dot])

J_omega = Matrix([
    [omega_x.diff(phi_dot), omega_x.diff(theta_dot), omega_x.diff(psi_dot)],
    [omega_y.diff(phi_dot), omega_y.diff(theta_dot), omega_y.diff(psi_dot)],
    [omega_z.diff(phi_dot), omega_z.diff(theta_dot), omega_z.diff(psi_dot)]
])

print("\n5. ROTATIONAL JACOBIAN J_ω:")
pprint(simplify(J_omega))

omega_check = simplify(J_omega * euler_rates)
print("\nVerification ω = J_ω * [φ̇, θ̇, ψ̇]^T:")
pprint(omega_check)

print("\n6. BODY-FRAME ANGULAR VELOCITY")
print("===============================")

omega_body = simplify(R.transpose() * omega_inertial)

print("Angular velocity in body frame (p, q, r):")
print("p =", omega_body[0])
print("q =", omega_body[1])
print("r =", omega_body[2])

J_omega_body = simplify(R.transpose() * J_omega)
print("\nBody frame Jacobian J_Ωb = R^T * J_ω:")
pprint(J_omega_body)

# Seesaw rotation matrices
R_B_theta1 = Matrix([
    [cos(theta1), 0, sin(theta1)],
    [0, 1, 0],
    [-sin(theta1), 0, cos(theta1)]
])

R_B_phi1 = Matrix([
    [1, 0, 0],
    [0, cos(phi1), -sin(phi1)],
    [0, sin(phi1), cos(phi1)]
])

R_B_theta2 = Matrix([
    [cos(theta2), 0, sin(theta2)],
    [0, 1, 0],
    [-sin(theta2), 0, cos(theta2)]
])

R_B_phi2 = Matrix([
    [1, 0, 0],
    [0, cos(phi2), -sin(phi2)],
    [0, sin(phi2), cos(phi2)]
])

R_dot_base = R.diff(phi) * phi_dot + R.diff(theta) * theta_dot + R.diff(psi) * psi_dot

def compute_extended_jacobian(R_B, R_B_dot, rate_symbol):
    R_ext = R * R_B
    R_ext_dot = R_dot_base * R_B + R * R_B_dot
    S_omega_ext = simplify(R_ext_dot * R_ext.transpose())

    omega_x = S_omega_ext[2, 1]
    omega_y = S_omega_ext[0, 2]
    omega_z = S_omega_ext[1, 0]

    J_ext = Matrix([
        [omega_x.diff(phi_dot), omega_x.diff(theta_dot), omega_x.diff(psi_dot), omega_x.diff(rate_symbol)],
        [omega_y.diff(phi_dot), omega_y.diff(theta_dot), omega_y.diff(psi_dot), omega_y.diff(rate_symbol)],
        [omega_z.diff(phi_dot), omega_z.diff(theta_dot), omega_z.diff(psi_dot), omega_z.diff(rate_symbol)],
    ])

    return simplify(J_ext)


# Compute dot matrices
R_B_theta1_dot = R_B_theta1.diff(theta1) * theta1_dot
R_B_theta2_dot = R_B_theta2.diff(theta2) * theta2_dot
R_B_phi1_dot = R_B_phi1.diff(phi1) * phi1_dot
R_B_phi2_dot = R_B_phi2.diff(phi2) * phi2_dot

# Extended Jacobians and error verification
J_omega_theta1 = compute_extended_jacobian(R_B_theta1, R_B_theta1_dot, theta1_dot)
J_omega_theta2 = compute_extended_jacobian(R_B_theta2, R_B_theta2_dot, theta2_dot)
J_omega_phi1 = compute_extended_jacobian(R_B_phi1, R_B_phi1_dot, phi1_dot)
J_omega_phi2 = compute_extended_jacobian(R_B_phi2, R_B_phi2_dot, phi2_dot)

print("\nExtended Jacobian J_ω_theta1:")
pprint(J_omega_theta1)

print("\nExtended Jacobian J_ω_theta2:")
pprint(J_omega_theta2)

print("\nExtended Jacobian J_ω_phi1:")
pprint(J_omega_phi1)

print("\nExtended Jacobian J_ω_phi2:")
pprint(J_omega_phi2)
