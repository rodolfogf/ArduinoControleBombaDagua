import pandas as pd
import matplotlib.pyplot as plt

leituras = pd.read_csv(
    r'C:\_UEMG\Disciplinas\Controle e Servomecanismo\Trabalho1_ControleBomba2\CoolTerm Capture 2023-02-08 21-43-37.txt.csv',
    sep=';')
pd.set_option('display.max_rows', 10)

leituras['nivel'] = leituras['nivel'].apply(lambda x: x - 2.09)
leituras = leituras.drop(leituras[leituras.nivel < 0].index)

tempo = leituras['tempo']
nivel = leituras['nivel']

maximos = leituras.groupby('tempo').max()
minimos = leituras.groupby('tempo').min()
medias = leituras.groupby('tempo').mean()
desvpad = leituras.groupby('tempo').std()

fig = plt.figure(figsize=(10, 7))
plt.plot(tempo, nivel)
plt.show()