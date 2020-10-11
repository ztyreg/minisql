const {exec} = require("child_process");
const path = require('path');
const express = require("express");
const bodyParser = require('body-parser')
const app = express();

app.use(bodyParser.json())

const exe = '../cmake-build-debug/src/Minisql';

const bash = function (command, res) {
    exec(command, (error, stdout, stderr) => {
        if (error) {
            res.status(401);
            return res.send({output: `${error.message}`});
        }
        if (stderr) {
            res.status(401);
            return res.send({output: `${stderr}`});
        }
        res.status(200);
        return res.send({output: `${stdout}`});
    });
};

app.post('/exec', async (req, res) => {
    const command = req.body.command;
    return bash(`${exe} -c "${command}"`, res);
});

app.post('/dbfile', async (req, res) => {
    return bash('xxd dbfile', res);
});

//loading all files in public folder
//see instructions in https://expressjs.com/en/starter/static-files.html
app.use(express.static('client'));

app.listen(8080);

console.log("Running at Port 8080");
