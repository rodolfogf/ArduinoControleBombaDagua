import pandas as pd
import matplotlib.pyplot as plt
from scipy import stats


def subtrair(a, b):
    return a - b


leituras = pd.read_csv(
    r'C:\_UEMG\Disciplinas\Controle e Servomecanismo\Trabalho1_ControleBomba2\CoolTerm Capture 2023-02-08 21-43-37.txt.csv',
    sep=';')
pd.set_option('display.max_rows', 10)

# i = leituras['tempo'].tolist().index(21.00)
# j = leituras['tempo'].tolist().index(22.00)
# leituras = leituras[i:j]

leituras['nivel'] = leituras['nivel'].apply(lambda x: x - 2.09)

print(leituras)
