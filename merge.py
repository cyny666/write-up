import os
import markdown2

def merge_markdown_files(folder_path, output_file):
    # 遍历文件夹中的所有文件和子文件夹
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            # 检查文件扩展名是否为.md或.markdown
            if file.lower().endswith(('.md', '.markdown')):
                file_path = os.path.join(root, file)
                # 读取Markdown文件的内容
                with open(file_path, 'r', encoding='utf-8') as md_file:
                    md_content = md_file.read()
                # 将Markdown内容追加到输出文件
                with open(output_file, 'a', encoding='utf-8') as output:
                    output.write(md_content)
                    output.write('\n\n')  # 添加换行分隔每个文件的内容

if __name__ == "__main__":
    # 指定文件夹路径和输出文件路径
    folder_path = './'
    output_file = 'merged_markdown.md'

    # 清空输出文件内容（如果文件存在）
    with open(output_file, 'w', encoding='utf-8'):
        pass

    # 调用函数合并Markdown文件
    merge_markdown_files(folder_path, output_file)

    print(f"All Markdown files in '{folder_path}' have been merged into '{output_file}'.")
