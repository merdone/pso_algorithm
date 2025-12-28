import argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import Button
import sys

class PSOVisualizer:
    def __init__(self, map_file, csv_file):
        self.map_file = map_file
        self.csv_file = csv_file
        self.is_running = False
        self.frame_idx = 0
        
        self.grid, self.w, self.h = self.load_map(map_file)
        self.grouped, self.iterations = self.load_results(csv_file)
        self.max_frames = len(self.iterations)

        self.fig, self.ax = plt.subplots(figsize=(10, 8))
        plt.subplots_adjust(bottom=0.2)

        valid_values = self.grid[self.grid > -999]
        if len(valid_values) > 0:
            vmin, vmax = np.min(valid_values), np.max(valid_values)
        else:
            vmin, vmax = -1000, 100

        self.im = self.ax.imshow(self.grid, origin='upper', cmap='plasma', extent=[0, self.w, self.h, 0], vmin=vmin, vmax=vmax)
        self.fig.colorbar(self.im, ax=self.ax, label='Signal')

        self.scat = self.ax.scatter([], [], c='cyan', s=30, label='Particles', edgecolors='black', linewidth=0.5)
        self.gbest_scat = self.ax.scatter([], [], c='white', marker='*', s=200, label='Leader', edgecolors='black')

        self.ax.set_title("PSO Visualization")
        self.ax.legend(loc='upper right')
        
        ax_prev = plt.axes([0.3, 0.05, 0.1, 0.075])
        self.btn_prev = Button(ax_prev, '< Iteration')
        self.btn_prev.on_clicked(self.step_backward)

        ax_play = plt.axes([0.45, 0.05, 0.1, 0.075])
        self.btn_play = Button(ax_play, 'Play/Pause')
        self.btn_play.on_clicked(self.toggle_play)

        ax_next = plt.axes([0.6, 0.05, 0.1, 0.075])
        self.btn_next = Button(ax_next, 'Iteration >')
        self.btn_next.on_clicked(self.step_forward)

        self.ani = animation.FuncAnimation(
            self.fig, 
            self.update, 
            frames=self.frame_generator, 
            interval=100,
            repeat=True,
            save_count=self.max_frames
        )

    def load_map(self, filename):
        try:
            with open(filename, 'r') as f:
                content = f.read().split()
            width, height = int(content[0]), int(content[1])
            values = [float(v) for v in content[2:]]
            grid = np.array(values).reshape((height, width))
            return grid, width, height
        except Exception as e:
            print(f"Map mistake {e}")
            sys.exit(1)

    def load_results(self, filename):
        try:
            df = pd.read_csv(filename)
            grouped = df.groupby('iteration')
            iterations = sorted(grouped.groups.keys())
            if not iterations: raise ValueError("Пустой CSV")
            return grouped, iterations
        except Exception as e:
            print(f"CSV mistake: {e}")
            sys.exit(1)

    def frame_generator(self):
        while True:
            if self.is_running:
                self.frame_idx = (self.frame_idx + 1) % self.max_frames
            yield self.frame_idx

    def toggle_play(self, event):
        self.is_running = not self.is_running

    def step_forward(self, event):
        self.is_running = False
        self.frame_idx = (self.frame_idx + 1) % self.max_frames
        self.fig.canvas.draw_idle()

    def step_backward(self, event):
        self.is_running = False
        self.frame_idx = (self.frame_idx - 1) % self.max_frames
        self.fig.canvas.draw_idle()

    def update(self, i):
        current_iter = self.iterations[i]
        
        if current_iter in self.grouped.groups:
            df_iter = self.grouped.get_group(current_iter)

            offsets = np.c_[df_iter['x'], df_iter['y']]
            self.scat.set_offsets(offsets)

            best = df_iter.loc[df_iter['fitness'].idxmax()]
            self.gbest_scat.set_offsets(np.c_[best['x'], best['y']])

            status = "Play" if self.is_running else "Pause"
            self.ax.set_title(f"PSO Visualization")
            self.ax.set_xlabel(f'Iteration: {current_iter} | Max Signal: {best["fitness"]:.2f} [{status}]')

        return self.scat, self.gbest_scat

    def show(self):
        plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("map_file", help="map file")
    parser.add_argument("--csv", default="results.csv", help="result file")
    args = parser.parse_args()

    viz = PSOVisualizer(args.map_file, args.csv)
    viz.show()