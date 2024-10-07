from flask import Flask, render_template, request, redirect, url_for
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index5.html')

@app.route('/nqueens')
def nqueens_index():
    return render_template('input1.html')

@app.route('/cryptarithmetic')
def cryptarithmetic_index():
    return render_template('input2.html')

@app.route('/jug')
def jug_index():
    return render_template('input4.html')

@app.route('/nqueens/input', methods=['GET', 'POST'])
def nqueens_input():
    if request.method == 'POST':
        nqueens_input = request.form['nqueens_input']

        cpp_process = subprocess.Popen(
            [r'C:\Users\prave\OneDrive\Documents\New folder\output\nqueens.exe'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        input_data = f'{nqueens_input}\n'
        output, error = cpp_process.communicate(input=input_data)

        if cpp_process.returncode == 0:
            return render_template('output1.html', output=output)
        else:
            return f"Error running C++ program:\n{error}"

    return render_template('input1.html')

@app.route('/cryptarithmetic/input', methods=['GET', 'POST'])
def cryptarithmetic_input():
    if request.method == 'POST':
        n = int(request.form.get('n'))
        expressions = []

        for i in range(n):
            expression = request.form.get(f'expression{i}')
            expressions.append(expression)

        result_expression = request.form.get('resultExpression')

        cpp_process = subprocess.Popen(
            [r'C:\Users\prave\OneDrive\Documents\New folder\output\cra.exe'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        input_data = f'{n}\n'
        for expression in expressions:
            input_data += f'{expression}\n'
        input_data += f'{result_expression}\n'

        output, error = cpp_process.communicate(input=input_data)

        if cpp_process.returncode == 0:
            return render_template('output2.html', solution=output)
        else:
            return f"Error running C++ program:\n{error}"

    return render_template('input2.html')

@app.route('/jug/input', methods=['POST'])
def jug_input():
    if request.method == 'POST':
        jug1 = int(request.form['jug1'])
        jug2 = int(request.form['jug2'])
        target = int(request.form['target'])

        cpp_process = subprocess.Popen(
            [r'C:\Users\prave\OneDrive\Documents\New folder\output\waterjug.exe'],  # Replace with the correct path
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        input_data = f'{jug1}\n{jug2}\n{target}\n'
        output, error = cpp_process.communicate(input=input_data)

        if cpp_process.returncode == 0:
            return render_template('output4.html', solution=output)
        else:
            return f"Error running C++ program:\n{error}"

    return render_template('input4.html')

if __name__ == '__main__':
    app.run(debug=True)
