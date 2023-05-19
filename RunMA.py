import multiprocessing
import os
from subprocess import call
import csv


def compile_results(output_filename, input_prefix):
    input_file_names = [file_name for file_name in os.listdir() if input_prefix in file_name]
    input_file_names.sort()
    print(input_file_names)
    with open(output_filename, mode='w') as output_file:
        out_writer = csv.writer(output_file, delimiter=",")
        out_writer.writerow(["Instance", "TW", "Time"])

        for file_name in input_file_names:
            with open(file_name, mode='r') as input_file:
                for row in input_file:
                    print(row.strip("\n").split(", "))
                    out_writer.writerow(row.strip("\n").split(", "))

    for input_file in input_file_names:
        os.remove(input_file)


def run_with_args(call_args):
    call(call_args)


if __name__ == "__main__":

    path = "PFSP_instances"
    instances = os.listdir(path)
    instances.sort()
    print(instances)

    processes = list()
    for instance in instances[:10]:
        print(instance)
        p = multiprocessing.Process(target=run_with_args,
                                    args=(["./pfspwt", "--ils", "--" + instance, path + "/" + instance],))
        processes.append(p)

    print("here")
    for i in range(len(processes)//10):
        for p in processes[i * 10:i * 10 + 10]:
            p.start()

        for p in processes[i * 10:i * 10 + 10]:
            p.join()


    compile_results("ILS_results/ils_results_time_normal_bestimprove", "--ils--DD")
