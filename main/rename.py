import os

def rename_sy_to_c(directory):
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith(".sy"):
                new_filename = os.path.join(root, filename.replace(".sy", ".c"))
                os.rename(os.path.join(root, filename), new_filename)

# 指定目录路径
directory_path = r"D:\360MoveData\Users\Luna\Desktop\main\testcase"

# 执行重命名操作
rename_sy_to_c(directory_path)