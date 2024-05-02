import os

def count_lines_by_semicolon(directory):
    line_count = 0
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(('.cpp', '.h')):
                with open(os.path.join(root, file), 'r') as f:
                    line_count += sum(1 for line in f if ';' in line)
    return line_count

def count_lines(directory):
    line_count = 0
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(('.cpp', '.h')):
                with open(os.path.join(root, file), 'r') as f:
                    line_count += sum(1 for line in f)
    return line_count

print("Count lines (\\n)", count_lines('src'))
print("Count lines ( ;)", count_lines_by_semicolon('src'))