import os

def count_lines(directory):
    line_count = 0
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(('.cpp', '.h')):
                with open(os.path.join(root, file), 'r') as f:
                    line_count += sum(1 for line in f)
    return line_count

print(count_lines('src'))