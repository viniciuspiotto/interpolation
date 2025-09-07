import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def load_and_prepare_data(filename="error.csv"):
    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"Erro: file '{filename}' not found")
        return None

    df['Function'] = df['Function'].ffill()
    df['Method'] = df['Method'].ffill()
    df['Mean_error'] = df['Mean_error'].replace(0, 1e-12)
    return df

def plot_separate_charts_by_method(df):
    if df is None:
        return

    methods = df['Method'].unique()

    if not os.path.exists('plots'):
        os.makedirs('plots')

    for method in methods:
        plt.figure(figsize=(11, 7))
        
        method_data = df[df['Method'] == method]
        
        ax = sns.lineplot(
            data=method_data,
            x='N',
            y='Mean_error',
            hue='Function',
            marker='o',
            linewidth=2.5
        )
        
        ax.set_yscale('log')
        ax.set_title(f'{method.replace('_', ' ')} Method', fontsize=16)
        ax.set_ylabel('Average error (log)', fontsize=12)
        ax.set_xlabel('Number of Points (N)', fontsize=12)
        ax.grid(True, which="both", ls="--")
        
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles=handles, labels=labels, title='Function Type', fontsize=11)
        
        filename = f"graph_{method}.png"
        
        plt.tight_layout()
        plt.savefig(f'plots/{filename}', dpi=300)
        plt.close()

if __name__ == "__main__":
    error_df = load_and_prepare_data(filename="error.csv")
    plot_separate_charts_by_method(error_df)
