##Este código foi oferecido por DATAI em https://www.kaggle.com/code/kanncaa1/water-quality-explanatory-data-analysis#
##A mudança realizada foi a inclusão do reajuste do limiar de classificação
#a fim de se gerar uma segunda pontuação para cada modelo e comparar as performances 

import numpy as np 
import pandas as pd 
import seaborn as sns
import matplotlib.pyplot as plt
import plotly.express as px
import missingno as msno
import statsmodels

# ML
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import RandomizedSearchCV, RepeatedStratifiedKFold, train_test_split
from sklearn.metrics import precision_score, confusion_matrix, recall_score
from sklearn import tree

df = pd.read_csv("water_potability.csv")

#Tratamento de valores ausentes por substituição pela média
df["ph"].fillna(value = df["ph"].mean(), inplace = True)
df["Sulfate"].fillna(value = df["Sulfate"].mean(), inplace = True)
df["Trihalomethanes"].fillna(value = df["Trihalomethanes"].mean(), inplace = True)

#Amostragem Holdout: Divisão dos conjuntos de treino e teste em proproção 70/30
X = df.drop("Potability", axis = 1).values
y = df["Potability"].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.3, random_state = 3)

#Normalização min-max nos conjuntos de treino e teste
x_train_max = np.max(X_train)
x_train_min = np.min(X_train)
X_train = (X_train - x_train_min)/(x_train_max-x_train_min)
X_test = (X_test - x_train_min)/(x_train_max-x_train_min)

#Criação dos modelos de Árvore de Decisão e Floresta Aleatória
models = [("DTC", DecisionTreeClassifier(max_depth = 3, criterion='entropy')),
          ("RF",RandomForestClassifier())]
finalResults = []
cmList1 = []
cmList2 = []

for name, model in models:
    #Treinamento dos modelos
    model.fit(X_train, y_train) 
    #Teste dos modelos
    model_result = model.predict(X_test)

    #Reajuste de limiar de classificação para comparação de perfomance
    #Nos experimentos, este código foi executado duas vezes, uma com o limiar alterado para 0,55 e outra com o limiar alterado para 0.3
    y_probs = model.predict_proba(X_test)[:, 1]
    new_threshold = 0.55
    y_pred_adjusted = (y_probs >= new_threshold).astype(int)

    #Cálculo de precisão e sensitividade para os modelos com limiar padrão 0.5
    score1 = precision_score(y_test, model_result)
    score3 = recall_score(y_test, model_result)

    #Cálculo de precisão e sensitividade para os modelos com limiar ajustado
    score2 = precision_score(y_test, y_pred_adjusted)
    score4 = recall_score(y_test, y_pred_adjusted)

    #Criação das matrizes de confusão padrão e com ajuste de limiar dos modelos
    cm1 = confusion_matrix(y_test, model_result)
    cm2 = confusion_matrix(y_test, y_pred_adjusted)

    #Listagem das pontuações finais
    finalResults.append((name, score1, score2, score3, score4))
    cmList1.append((name, cm1))
    cmList2.append((name,cm2))

#Visualização das pontuações finais
print("Scores: ")
print('[Model, precision_score_standard_threshold, precision_score_adjusted_threshold, recall_score_standard_threshold, recall_score_adjusted_threshold]')  
print(finalResults[0])
print(finalResults[1])
print("\n")

#Visualização da Árvore de Decisão
dt_clf = models[0][1]
print(dt_clf)
print("\n")
plt.figure(figsize = (50,50))
tree.plot_tree(dt_clf,
               feature_names =  df.columns.tolist()[:-1],
               class_names = ["Não Potável", "Potável"],
               filled = True,
               precision = 5)
plt.show()

#Visualização das matrizes de confusão
for name, i in cmList1:
   plt.figure()
   sns.heatmap(i, annot = True, linewidths = 0.8, fmt = ".1f")
   plt.title(name)
   plt.show()

for name, i in cmList2:
   plt.figure()
   sns.heatmap(i, annot = True, linewidths = 0.8, fmt = ".1f")
   plt.title(name)
   plt.show()