import os

def generate_assembly(directory, output_directory):
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith(".c"):
                input_file = os.path.join(root, filename)
                output_file = os.path.join(output_directory, filename.replace(".c", ".s"))
                command = f"gcc -S {input_file} -o {output_file}"
                os.system(command)

# 指定源代码文件所在的目录
source_directory = r"D:\360MoveData\Users\Luna\Desktop\main\testcase"

# 指定汇编文件的输出目录
output_directory = r"D:\360MoveData\Users\Luna\Desktop\main\S"

# 执行生成汇编文件操作
generate_assembly(source_directory, output_directory)
