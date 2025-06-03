import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Leer CSV
df = pd.read_csv('benchmark_results.csv')

def plot_metric_with_log_n(df, metric_col, ylabel, title, filename):
    plt.figure(figsize=(8,5))
    
    # Promediar resultados para cada tamaño (por si hay varias ejecuciones)
    avg_data = df.groupby('Size')[metric_col].mean()
    sizes = avg_data.index.values
    times = avg_data.values
    
    plt.plot(sizes, times, marker='o', label='Medido')
    
    # Curva O(log n) normalizada para comparación
    # Normalizamos para que el primer valor coincida con la medición
    log_n = np.log2(sizes)
    log_n_normalized = log_n * (times[0] / log_n[0])
    plt.plot(sizes, log_n_normalized, label='O(log n) referencia', linestyle='--')
    
    plt.xlabel('Tamaño (n)')
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.legend()
    plt.savefig(filename)
    plt.close()

# Graficar cada métrica
plot_metric_with_log_n(df, 'Insert_us', 'Tiempo promedio (µs)', 'Inserción promedio vs O(log n)', 'insert.png')
plot_metric_with_log_n(df, 'SearchExisting_us', 'Tiempo promedio (µs)', 'Búsqueda exitosa vs O(log n)', 'search_existing.png')
plot_metric_with_log_n(df, 'SearchMissing_us', 'Tiempo promedio (µs)', 'Búsqueda fallida vs O(log n)', 'search_missing.png')
plot_metric_with_log_n(df, 'Remove_us', 'Tiempo promedio (µs)', 'Eliminación promedio vs O(log n)', 'remove.png')
plot_metric_with_log_n(df, 'LeftRotate_us', 'Tiempo promedio (µs)', 'Rotación izquierda promedio vs O(log n)', 'left_rotate.png')
plot_metric_with_log_n(df, 'RightRotate_us', 'Tiempo promedio (µs)', 'Rotación derecha promedio vs O(log n)', 'right_rotate.png')

print("Gráficos generados y guardados: insert.png, search_existing.png, search_missing.png, remove.png, left_rotate.png, right_rotate.png")
