import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import io

def prepare_data(csv_data):
    df = pd.read_csv(io.StringIO(csv_data))
    df['Method'] = df['Method'].ffill()
    df['Function'] = df['Function'].ffill()
    df['Total_time'] = pd.to_numeric(df['Total_time'], errors='coerce')
    df['Total_time'] = df['Total_time'].replace(0, 1e-12)
    df.dropna(subset=['Total_time'], inplace=True)
    return df

def plot_separate_charts_by_method(df, output_filename="complexity_comparison.png"):
    if df is None or df.empty:
        print("O DataFrame está vazio. Nenhum gráfico será gerado.")
        return

    methods = sorted(df['Method'].unique())
    n_methods = len(methods)
    
    fig, axes = plt.subplots(1, n_methods, figsize=(n_methods * 6, 6), sharey=True)
    if n_methods == 1:
        axes = [axes]

    for ax, method in zip(axes, methods):
        method_data = df[df['Method'] == method]
        
        sns.lineplot(
            data=method_data,
            x='N',
            y='Total_time',
            hue='Function',
            marker='o',
            linewidth=2.5,
            ax=ax
        )
        
        ax.set_title(f'Método {method.replace("_", " ")}', fontsize=16)
        ax.set_ylabel('Complexidade de tempo (segundos)', fontsize=12)
        ax.set_xlabel('Número de pontos (N)', fontsize=12)
        ax.grid(True, which="both", ls="--")
        
        if ax.get_legend() is not None:
            ax.get_legend().remove()
    
    handles, labels = axes[-1].get_legend_handles_labels()
    fig.legend(handles, labels, title='Tipo de função', bbox_to_anchor=(1.0, 0.9), loc='upper left', fontsize=11)
    
    fig.suptitle('Comparação da Complexidade de Tempo por Método', fontsize=20, y=1.03)
    
    plt.tight_layout(rect=[0, 0, 0.9, 1])
    plt.savefig(output_filename, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Gráfico salvo como '{output_filename}'")

if __name__ == "__main__":
    complex_df = prepare_data("complex.csv")
    plot_separate_charts_by_method(complex_df)
