import helpers
import latex
import matplotlib.pyplot as plt


test_data = {
    4096: {
        1: 0,
        2: 1,
        3: 1,
        4: 5,
    },
    32768: {
        1: 2,
        2: 18,
        3: 4,
        4: 10,
    },
    131072: {
        1: 6,
        2: 17,
        3: 94,
        4: 224,
    },
    524288: {
        1: 26,
        2: 101,
        3: 274,
        4: 380,
    },
}

mid_data = {k: 0 for k in test_data[4096]}
for k, v in test_data.items():
    for k, v in v.items():
        mid_data[k] += v
mid_data = {k: int(v/len(mid_data)) for k, v in mid_data.items()}

def get_test_result(spins, data):
    plot = latex.LatexPicture(
        f'plot{spins}',
        f'График результатов тестирования для spins={spins}',
        f'plot{spins}',
    )

    table = latex.LatexTable(
        2, 'l', 
        caption=f'Результаты тестирования для spins={spins}',
        caption_pos='bottom', 
        label=f'results{spins}',
    )
    table.set_header('Кол-во потоков', 'Время выполнения (мс)')
    for n, t in data.items():
        table.add_row(n, t)
    
    title = f'\\subsection*{{Тест (spins={spins})}}'
    tab_paragraph = f'Результаты тестирования представленны в таблице \\ref{{{table.label}}}'
    plot_paragraph = f'График результатов тестирования представлен на рис.\\ref{{{plot.label}}}'
    result = '\n\n'.join((title, tab_paragraph, table.render(), plot_paragraph, plot.render()))
    return result

def get_mid():
    data = mid_data

    plot = latex.LatexPicture(
        f'plot_mid',
        f'График усреднённых результатов тестирования',
        f'plot_mid',
    )

    table = latex.LatexTable(
        2, 'l', 
        caption=f'Усреднённые результаты тестирования',
        caption_pos='bottom', 
        label=f'results_mid',
    )
    table.set_header('Кол-во потоков', 'Время выполнения (мс)')
    for n, t in data.items():
        table.add_row(n, t)
    
    title = f'\\subsection*{{Усреднённые результаты тестирования}}'
    tab_paragraph = f'Усреднённые результаты тестирования представленны в таблице \\ref{{{table.label}}}'
    plot_paragraph = f'График усреднённых результатов тестирования представлен на рис.\\ref{{{plot.label}}}'
    result = '\n\n'.join((title, tab_paragraph, table.render(), plot_paragraph, plot.render()))
    return result

def get_tests_results():
    sections = [get_test_result(spins, data) for spins, data in test_data.items()]
    sections.append(get_mid())
    return '\n\n'.join(sections)

def make_test_results():
    with open(
        '/home/kirill/CLionProjects/1lab-pas-3-2/'
        'report/modules/chapters/test_results.tex', 
        'w') as f:
        f.write(get_tests_results())

def make_plot(title, filename, data):
    plt.title(title)
    plt.xlabel('threads')
    plt.ylabel('execution time (ms)')
    plt.xticks([1, 2, 3, 4])
    plt.plot(data.keys(), data.values())
    # plt.savefig(filename)
    # plt.clf()

def make_plots():
    for k, v in test_data.items():
        make_plot(f'Test with {k} spins', f'report/photo/plot{k}', v)
    # make_plot(f'Average results', 'report/photo/plot_mid', mid_data)
    plt.title('All in one')
    plt.legend([f'{spins} spins' for spins in test_data])
    plt.savefig('report/photo/all_in_one')

def main():
    pass


if __name__ == '__main__':
    main()
