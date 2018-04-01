////////////////////// http server //////////////////////
var http = require("http");
var url = require('url');
var fs = require('fs');

var server = http.createServer(function(request, response) {
    var path = url.parse(request.url).pathname;
    console.log('Server on');
    switch (path) {
        case '/':
            response.writeHead(200, { 'Content-Type': 'text/html' });
            response.write('Hello, World.');
            response.end();
            break;
        default:
            fs.readFile(__dirname + path, function(error, data) {
                if (error) {
                    response.writeHead(404);
                    response.write("opps this doesn't exist - 404");
                } else {
                    response.writeHead(200, { "Content-Type": "text/html" });
                    response.write(data, "utf8");
                }
                response.end();
            });
    }
});
server.listen(8000);

////////////////////// serial port //////////////////////
// DEBUG=serialport:main node index.js
var SerialPort = require("serialport");
var port = new SerialPort("/dev/tty.usbmodem1411");
// port.on('data', function (data) {
//   console.log('Data:', data);
// });

//////////////////// socket io //////////////////////
// DEBUG=socket.io* node myapp
var io = require("socket.io");
var sio = io.listen(server);

var client = [];

port.on('data', function(data) {
    console.log('收到 ' + data);
    client.forEach((socket) => { socket.emit('serial', { 'control': data.toString() }) });
});

var p = 0;
sio.on('connection', function(socket) {
    console.log('socket here');
    // client in
    client.push(socket);
    // anouce index to client 
    socket.emit('index', { 'index': client.indexOf(socket) });

    if (client.indexOf(socket) == 0) {
        console.log("sdajkl;fldfjdlj");
        socket.emit('hasUser', { "hasUser": true });
    }

    socket.on('lives', function(data) {
        client.forEach((socket) => socket.emit('life', data));
    });

    socket.on('score', function(data) {
        client.forEach((socket) => socket.emit('score', data));
    });

    socket.on('restart', function(data) {
        var nowClient = socket;
        client.forEach(function(socket) {
            if (socket != nowClient) {
                socket.emit('restart', data);
            }
        });
    });

    socket.on('transition', function(data) {
        if (data == "right") {
            p = client.indexOf(socket) + 1;
            data = "left";
        } else if (data == "left") {
            p = client.indexOf(socket) - 1;
            data = "right";
        }
        p = (p + client.length) % client.length;
        socket.emit('entry', { "hasUser": false, "entryPoint": data });

        console.log("dsfsd: ", p);
        client.forEach((socket) => {
            var hasUser = client.indexOf(socket) === p;
            console.log(p, " : ", hasUser, " : ", data);
            socket.emit('entry', { "hasUser": hasUser, "entryPoint": data });
        });
    });

    // if client disconnect
    socket.on('disconnect', function() {
        // client out
        client.splice(client.indexOf(socket), 1);
        // update index of every client 
        client.forEach((socket) => { socket.emit('index', { 'index': client.indexOf(socket) }) });
        console.log('disconnected event');
    });

});

// https://blog.gtwang.org/programming/socket-io-node-js-realtime-app/
// https://www.npmjs.com/package/socket.io-serialport
// http://helloraspberrypi.blogspot.tw/2014/03/nodejssocketioserialport-web-app-to.html