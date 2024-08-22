#Este código foi oferecido por DATAI em https://www.kaggle.com/code/kanncaa1/water-quality-explanatory-data-analysis#
#As mudanças realizadas foram a correção de erros que surgiram ao executar o código original

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import plotly.express as px
import missingno as msno

df = pd.read_csv("water_potability.csv")

#Visualização da distribuição de classes
d = df['Potability'].value_counts().reset_index()
d.columns = ['Potability', 'Count']
fig = px.pie(d, values='Count', names=['Not Potable', 'Potable'], hole=0.35, opacity=0.8,
             labels={"label": "Potability", "Count": "Number of Samples"})
fig.update_layout(title=dict(text="Pie Chart of Potability Feature"))
fig.update_traces(textposition="outside", textinfo="percent+label")
fig.show()

#Visualização da correlação de variáveis
sns.clustermap(df.corr(), cmap = "vlag", dendrogram_ratio = (0.1, 0.2), annot = True, linewidths = .8, figsize = (9,10))
plt.show()

#Visualização de valores ausentes
msno.matrix(df)
plt.show()
print('Quatidade de valores nulos por atributo')
print(df.isnull().sum())

#Tratamento de valores ausentes por substituição pela média
df["ph"].fillna(value = df["ph"].mean(), inplace = True)
df["Sulfate"].fillna(value = df["Sulfate"].mean(), inplace = True)
df["Trihalomethanes"].fillna(value = df["Trihalomethanes"].mean(), inplace = True)
print('\n Quatidade de valores nulos por atributo apos pre-processamento')
print(df.isnull().sum())