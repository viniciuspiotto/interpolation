import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def carregar_e_preparar_dados(nome_arquivo="error.csv"):
    """
    Carrega os dados de um arquivo CSV, trata valores ausentes e renomeia colunas.
    """
    try:
        df = pd.read_csv(nome_arquivo)
    except FileNotFoundError:
        print(f"Erro: arquivo '{nome_arquivo}' não encontrado.")
        return None

    # Preenche valores ausentes para Função e Método
    df['Funcao'] = df['Function'].ffill()
    df['Metodo'] = df['Method'].ffill()
    
    # Substitui 0 por um valor muito pequeno para evitar problemas com a escala logarítmica
    df['Erro_Medio'] = df['Mean_error'].replace(0, 1e-12)
    
    return df

def plotar_graficos_separados_por_metodo(df):
    """
    Gera e salva gráficos de erro separados para cada método de interpolação.
    """
    if df is None:
        return

    metodos = df['Metodo'].unique()
    pasta_graficos = 'graficos'

    if not os.path.exists(pasta_graficos):
        os.makedirs(pasta_graficos)

    for metodo in metodos:
        plt.figure(figsize=(11, 7))

        dados_metodo = df[df['Metodo'] == metodo]

        ax = sns.lineplot(
            data=dados_metodo,
            x='N',
            y='Erro_Medio',
            hue='Funcao',
            marker='o',
            linewidth=2.5
        )

        ax.set_yscale('log')
        ax.set_title(f'Método: {metodo.replace("_", " ")}', fontsize=16)
        ax.set_ylabel('Erro Médio (escala log)', fontsize=12)
        ax.set_xlabel('Número de Pontos (N)', fontsize=12)
        ax.grid(True, which="both", ls="--")

        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles=handles, labels=labels, title='Tipo de Função', fontsize=11)

        nome_arquivo_saida = f"error_{metodo}.png"
        caminho_salvar = os.path.join(pasta_graficos, nome_arquivo_saida)

        plt.tight_layout()
        plt.savefig(caminho_salvar, dpi=300)
        plt.close()
        
        print(f"Gráfico salvo em: {caminho_salvar}")

if __name__ == "__main__":
    df_erro = carregar_e_preparar_dados(nome_arquivo="error.csv")
    plotar_graficos_separados_por_metodo(df_erro)