import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/naor/Desktop/naor/study/Thesis/install/drone_tunner'
