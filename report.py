import os
import subprocess
import pandas as pd

main_dir = 'mains'
input_dir = 'inputs'
output_dir = 'outputs'

# Generate inputs
inputs = []
for i in range(10):
    num_films = str(1000 * (i + 1))
    for j in range(10):
        num_cats = str(j + 2)
        inputs.append(num_films + ' ' + num_cats) # Ex: 1000 2, 1000 3, ..., 10000 10
for input_params in inputs:
    input_path = os.path.join(input_dir, 'input_gen') # Ex: inputs/input_gen
    input_file = input_params.replace(' ', '_') + '.txt' # Ex: 1000_2.txt, 1000_3.txt, ..., 10000_10.txt
    input_args = input_params.split() # Ex: ['1000', '2'], ['1000', '3'], ..., ['10000', '10']
    with open(os.path.join(input_dir, input_file), 'w') as f:
        subprocess.run([input_path, *input_args], stdout=f)

#Rodar no terminal para main_v1 (sem heurística)
with open(f"runScript/runScrip_v1.txt", "w") as output_file:
    for input in inputs:
        input_file = input.replace(' ', '_')
        output_file.write(f"mains/main_v1 < inputs/{input_file}.txt > outputs/v1/v1_output_{input_file}.txt\n")

#Rodar no terminal para main_v2 (com heurística de aleatoriedade)
with open(f"runScript/runScrip_v2.txt", "w") as output_file:
    for input in inputs:
        input_file = input.replace(' ', '_')
        output_file.write(f"mains/main_v2 < inputs/{input_file}.txt > outputs/v2/v2_output_{input_file}.txt\n")

df_v1 = pd.DataFrame(columns=['num_films', 'num_cats', 'num_films_allocated', 'screentime', 'runtime'])
v1_outputs = []
output_dir_v1 = output_dir + '/v1'
for output_file in os.listdir(output_dir_v1):
    with open(os.path.join(output_dir_v1, output_file), 'r') as f:
        output_data = f.read().splitlines()
        total_num_films, num_cats, num_films_allocated , screentime, runtime = output_data[0], output_data[1], output_data[2], output_data[3], output_data[4]
        #append the values as int and append to the list
        v1_outputs.append([int(total_num_films), int(num_cats), int(num_films_allocated), int(screentime), int(runtime)])
df_v1 = pd.DataFrame(v1_outputs, columns=['num_films', 'num_cats', 'num_films_allocated', 'screentime', 'runtime'])
df_v1 = df_v1.sort_values(by=['num_films', 'num_cats'], ascending=[True, True]).reset_index(drop=True)

df_v2 = pd.DataFrame(columns=['num_films', 'num_cats', 'num_films_allocated', 'screentime', 'runtime'])
v2_outputs = []
output_dir_v2 = output_dir + '/v2'
for output_file in os.listdir(output_dir_v2):
    with open(os.path.join(output_dir_v2, output_file), 'r') as f:
        output_data = f.read().splitlines()
        total_num_films, num_cats, num_films_allocated , screentime, runtime = output_data[0], output_data[1], output_data[2], output_data[3], output_data[4]
        #append the values as int and append to the list
        v2_outputs.append([int(total_num_films), int(num_cats), int(num_films_allocated), int(screentime), int(runtime)])
df_v2 = pd.DataFrame(v2_outputs, columns=['num_films', 'num_cats', 'num_films_allocated', 'screentime', 'runtime'])
df_v2 = df_v2.sort_values(by=['num_films', 'num_cats'], ascending=[True, True]).reset_index(drop=True)