import pandas as pd
import matplotlib.pyplot as plt
from scipy import stats

leituras = pd.read_csv(
    r'C:\_UEMG\Disciplinas\Controle e Servomecanismo\Trabalho1_ControleBomba2\CoolTerm Capture 2023-02-08 21-43-37.txt.csv',
    sep=';')
pd.set_option('display.max_rows', 10)

# i = leituras['tempo'].tolist().index(21.00)
# j = leituras['tempo'].tolist().index(22.00)
# leituras = leituras[i:j]

leituras['nivel'] = leituras['nivel'].apply(lambda x: x - 2.09)
leituras = leituras.drop(leituras[leituras.nivel < 0].index)

tempo = leituras['tempo']
nivel = leituras['nivel']

maximos = leituras.groupby('tempo').max()
minimos = leituras.groupby('tempo').min()
medias = leituras.groupby('tempo').mean()
desvpad = leituras.groupby('tempo').std()

# print(f'Máximos:\n{maximos}\n')
# print(f'Mínimos:\n{minimos}\n')
# print(f'Médias:\n{medias}\n')
# print(f'Mínimos:\n{desvpad}\n')

fig = plt.figure(figsize=(10, 7))
plt.plot(tempo, nivel)
plt.show()

#plt.boxplot(nivel[:j])
#plt.show()

# q1 = leituras.groupby('tempo').quantile(0.25)
# q3 = leituras.groupby('tempo').quantile(0.75)
# print(q1)
# print(q3)