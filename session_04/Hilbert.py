import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg as la
import math
from pprint import pprint

a = int(input("Enter row"))
b = int(input("Enter column"))

def hilmat(a, b):
    return [[1 / (i + j + 1) for j in range(b)] for i in range(a)]

results = la.eig(hilmat(a,b))

pprint(hilmat(a, b))

print("Eigenvalues")
print (results[0])
print("Eigenvectors")
print (results[1])
