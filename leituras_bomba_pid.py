import pandas as pd
import matplotlib.pyplot as plt

leituras = pd.read_csv(
    r'C:\_UEMG\Disciplinas\Controle e Servomecanismo\Trabalho1_ControleBomba2\LeiturasPID_50-0.1-55.csv',
    sep=';')
pd.set_option('display.max_rows', None)

#---------------------- Plot do gravação sem correções e normalização ------------------------#
'''
tempo = leituras['tempo']
nivel = leituras['nivel']

fig = plt.figure(figsize=(10, 7))
plt.plot(tempo, nivel)
plt.show()
'''
#---------------------------------------------------------------------------------------------#

#---------------------------------- Correções e normalização ---------------------------------#

leituras['tempo'] = leituras['tempo'].apply(lambda y: y - 10)
leituras['nivel'] = leituras['nivel'].apply(lambda x: x - 2.51)
leituras = leituras.drop(leituras[leituras.nivel < 0].index)
leituras = leituras.reset_index().drop(columns=['index'])

tempo = leituras['tempo']
nivel = leituras['nivel']

# maximos = leituras.groupby('tempo').max()
# minimos = leituras.groupby('tempo').min()
medias = leituras.groupby('tempo').mean()['nivel']
desvpad = leituras.groupby('tempo').std()['nivel']

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

fig = plt.figure(figsize=(10, 7))
plt.plot(tempo_list, medias_corrigido)
plt.show()

