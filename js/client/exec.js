// const text_command = document.getElementById('command');
const text_output = document.getElementById('output');
const button_execute = document.getElementById('execute');
const button_dbfile = document.getElementById('dbfile');

const http = new EasyHTTP();

// // https://thecodebarbarian.com/building-a-code-editor-with-codemirror.html
// text_command.value = 'create table student(\n' +
//     '\tid int,\n' +
//     '\tname char(12) unique,\n' +
//     '\tscore float,\n' +
//     '\tprimary key(id) \n' +
//     ');\n\n';
// text_command.value +=
//     '-- Anything after "--" is comment\n';
// text_command.value +=
//     '-- Click "Execute" below to create the "student" table\n\n';
// text_command.value +=
//     '-- Currently you can only run one command at a time.\n\n';

init_code = 'create table student(\n' +
    '\tid int,\n' +
    '\tname char(12) unique,\n' +
    '\tscore float,\n' +
    '\tprimary key(id) \n' +
    ');\n\n';
init_code +=
    '-- Anything after "--" is comment\n\n';
init_code +=
    '-- Click "Execute" below to create "student" table\n';
init_code +=
    '-- If it already exists, run\n';
init_code +=
    '-- drop table student;\n';
init_code +=
    '-- In this web demo, only one command can be run at a time\n\n';
init_code +=
    '-- You can also try the following commands\n';
init_code +=
    '-- insert into student values(1080100001, \'name1\', 99);\n';
init_code +=
    '-- insert into student values(1080100002, \'name2\', 92);\n';
init_code +=
    '-- select * from student where id=1080100001;\n';
init_code +=
    '-- select * from student where id<>1080100001;\n';
init_code +=
    '-- select * from student;\n';



var myCodeMirror = CodeMirror(document.querySelector('#command'), {
    lineNumbers: true,
    value: init_code,
    mode: 'sql',
    font: 'monaco',
    lineWrapping: true
});


// code_command.textContent += 'insert into student values(1080100001, \'name1\' ,99);\n\n';
// code_command.textContent += 'insert into student values(1080100002, \'name2\' ,90);\n\n';
// code_command.textContent += 'select * from student;';

text_output.textContent = "Welcome to MiniSQL shell!\n\n" +
    //"A new database file is created every time this page is loaded.\n\n" +
    'See "About" for features.\n' +
    'See "MiniSQL Syntax" for all syntax.\n' +
    'See "Sample Commands" for examples.\n\n' +
    'Write commands in the editor and click "Execute" to run it on server.\n\n' +
    'You can also view the raw database file by clicking "Database File" below. ' +
    'The binary database file is dumped using the "xxd" command.\n\n';

button_execute.addEventListener('click', (e) => {
    const command = myCodeMirror.getValue();
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
