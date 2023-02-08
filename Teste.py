import pandas as pd
import matplotlib as plt
from IPython.core.display_functions import display

dic = {
    "seq": [0, 1, 2, 3, 4, 5, 6, 7, 8],
    "val": [3, 4, 5, 5, 5, 6, 7, 8, 9]
}

teste = pd.DataFrame(dic)
q1 = teste.quantile(0.25)
q3 = teste.quantile(0.75)

iqr = q3['val'] - q1['val']
li = q1['val'] - iqr * 1.5
ls = q3['val'] + iqr * 1.5

teste_corrigido = teste[(teste['val'] > li) & (teste['val'] < ls)]
display(teste_corrigido)
