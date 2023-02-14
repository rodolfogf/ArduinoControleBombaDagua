import pandas as pd
import matplotlib.pyplot as plt

leituras = pd.read_csv(
    r'C:\_UEMG\Disciplinas\Controle e Servomecanismo\Trabalho1_ControleBomba2\CoolTerm Capture 2023-02-08 21-43-37.txt.csv',
    sep=';')
pd.set_option('display.max_rows', None)

leituras['nivel'] = leituras['nivel'].apply(lambda x: x - 2.09)
leituras = leituras.drop(leituras[leituras.nivel < 0].index)
leituras = leituras.reset_index().drop(columns=['index'])

tempo = leituras['tempo']
nivel = leituras['nivel']

'''
q1 = leituras.groupby('tempo').quantile(0.25)
q3 = leituras.groupby('tempo').quantile(0.75)
iqr = q3 - q1
li = q1 - 1.5 * iqr
ls = q3 + 1.5 * iqr
li = li['nivel']
ls = ls['nivel']
'''

# maximos = leituras.groupby('tempo').max()
# minimos = leituras.groupby('tempo').min()
medias = leituras.groupby('tempo').mean()['nivel']
desvpad = leituras.groupby('tempo').std()['nivel']

# teste = li['nivel'][0]

# leituras = leituras.drop(leituras[leituras.nivel < 0].index)
# teste = li.query('tempo == 70')
# teste2 = li.loc[70]

leituras_corrigidas = leituras

for i, t in enumerate(tempo):
    if nivel.loc[i] < (medias.loc[t] - 2 * desvpad.loc[t]):
        leituras_corrigidas.drop([i], inplace=True)

    # print(f'{i} {tempo.loc[i]:.0f} {nivel.loc[i]:.2f} {medias.loc[t]:.2f} {desvpad.loc[t]:.2f} {acao}')

leituras_corrigidas = leituras_corrigidas.reset_index().drop(columns=['index'])

tempo_corrigido = leituras_corrigidas['tempo']
nivel_corrigido = leituras_corrigidas['nivel']

medias_corrigido = leituras.groupby('tempo').mean()['nivel']

tempo_list = list(set(leituras_corrigidas['tempo'].tolist()))

# print(leituras)
print(leituras_corrigidas)
# print(leituras_corrigidas.iloc[629])

fig = plt.figure(figsize=(10, 7))
# plt.plot(tempo, nivel)
# plt.plot(tempo_corrigido, nivel_corrigido)
plt.plot(tempo_list, medias_corrigido)
plt.show()
