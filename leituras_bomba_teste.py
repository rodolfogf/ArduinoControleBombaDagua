import pandas as pd
import statistics
import matplotlib.pyplot as plt
from IPython.core.display_functions import display

leituras = pd.read_csv(
    r'C:\_UEMG\Disciplinas\Controle e Servomecanismo\Trabalho1_ControleBomba2\CoolTerm Capture 2023-02-08 21-43-37.txt.csv',
    sep=';')
pd.set_option('display.max_rows', None)

i = leituras['tempo'].tolist().index(20.00)
#j = leituras['tempo'].tolist().index(23.00)

leituras = leituras[i:]
leituras = leituras.reset_index().drop(columns=['index'])

tempo = list(set(leituras['tempo'].tolist()))
mediana = pd.DataFrame()
moda = pd.DataFrame()

for i, t in enumerate(tempo):
    tmp_df = leituras[leituras['tempo'] == t]
    #mdn = statistics.median(tmp_df['nivel'])
    #md = statistics.mode(tmp_df['nivel'])

    #print(f't:{t} Mediana: {mdn} Moda: {md}')
    print(f't:{t}')






