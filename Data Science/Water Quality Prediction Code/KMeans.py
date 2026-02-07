#Este código foi oferecido por DATAI em https://www.kaggle.com/code/kanncaa1/water-quality-explanatory-data-analysis#
#As mudanças realizadas foram a criação do modelo não supervisionado, com a adição do método k-means e outros associados

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import plotly.express as px
import missingno as msno

#ML
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.metrics import adjusted_rand_score, rand_score
from sklearn.preprocessing import normalize

df = pd.read_csv("water_potability.csv")

#Tratamento de valores ausentes por substituição pela média
df["ph"].fillna(value = df["ph"].mean(), inplace = True)
df["Sulfate"].fillna(value = df["Sulfate"].mean(), inplace = True)
df["Trihalomethanes"].fillna(value = df["Trihalomethanes"].mean(), inplace = True)

#Grafico de Inércia para visualização do número ideal de clusters
inertias = []
for i in range(1,11):
    kmeans = KMeans(n_clusters=i)
    kmeans.fit(df)
    inertias.append(kmeans.inertia_)

plt.plot(range(1,11), inertias, marker='o')
plt.xlabel('Number of clusters')
plt.ylabel('Inertia')
plt.show()

##Os clustes foram gerados para utilizando todo o dataset, porém, 
#não houve mudança significativa nos resultados com o uso de todos os dados ou de apenas uma amostra de 500 dados, então
#geramos a representação gráfica dos clusters com apenas 500 pontos para melhor visualização
sample = df.sample(500)
normalize(sample)

#Obtenção das componentes principais para visualização dos clusters criados
pca_2 = PCA(n_components=2)
pca_2_result = pca_2.fit_transform(sample)
dataset_pca = pd.DataFrame(abs(pca_2.components_), columns=df.columns, index=['PC_1', 'PC_2'])

#Realização do k-means para dois clusters e listagem dos pontos em termos das componentes principais para a visualização
kmeans = KMeans(n_clusters=2)
kmeans = kmeans.fit(sample)

x = []
y = []

for value in pca_2_result:
    x.append(value[0])
    y.append(value[1])
    i = i+1

#Obtenção das coordenadas dos centroides
pca_centers = PCA(n_components=2)
pca_centers_result = pca_centers.fit_transform(kmeans.cluster_centers_)
center1 = pca_centers_result[0]
center2 = pca_centers_result[1]

#Visualização dos Clusters
plt.scatter(x, y, c=kmeans.labels_)
plt.scatter(center1[0], center1[1], color='red', marker='+', label='Center 1')
plt.scatter(center2[0], center2[1], color='blue', marker='+', label='Center 2')
plt.xlabel((dataset_pca[dataset_pca > 0.3].iloc[0]).dropna())
plt.ylabel((dataset_pca[dataset_pca > 0.3].iloc[1]).dropna())
plt.show()

#Cálculo do Rand Index e Adjusted Rand Index
true_labels = sample['Potability'].values  
ri2 = rand_score(true_labels, kmeans.labels_)
print(f'Rand Index: {ri2}')
ari = adjusted_rand_score(true_labels, kmeans.labels_)
print(f'Adjusted Rand Index: {ari}')
