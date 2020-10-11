const text_command = document.getElementById('command');
const text_output = document.getElementById('output');
const button_execute = document.getElementById('execute');
const button_dbfile = document.getElementById('dbfile');

const http = new EasyHTTP();

text_output.textContent = "Welcome to MiniSQL shell!\n\n" +
    "A new database file is created every time this page is loaded.\n\n" +
    'See "About" for features.\n' +
    'See "MiniSQL Syntax" for all syntax.\n' +
    'See "Sample Commands" for examples.\n\n' +
    'Write commands in the editor and click "Execute" to run it on server.\n\n' +
    'You can also view the raw database file by clicking "Database File"\n\n';

button_execute.addEventListener('click', (e) => {
    const command = text_command.value
    http.post('/exec', {command})
        .then(res => {
            text_output.textContent = res.output;
        });
});

button_dbfile.addEventListener('click', (e) => {
    http.post('/dbfile', {})
        .then(res => {
            text_output.textContent = res.output;
        });
});
