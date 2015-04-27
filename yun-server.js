var PORT = 8000;

var skateboard = require('skateboard');
var fs = require('fs');
var url = require('url');

// keep track of the connected clients
var clients = []

var options = {
  port : PORT,
  requestHandler: function(request, response) {
    var query = url.parse(request.url, true).query;

    clients.forEach(function(client) {
      client.write(JSON.stringify(query));
    });

    console.log('-----')
    console.log('got a', request.method, 'on url', request.url);
    console.log(request.headers);
    console.log('');

    if (query && query.test) {
      fs.writeFile('C:\\Users\\dev1\\Documents\\Arduino - Dragino Yun Shield\\test.txt', query.test, function(error) {
        if (error) {
          throw error;
        }
        response.end('ok');
      });
    }
  }
}


// setup the skateboard server which will serve html and create a websocket connection
skateboard(options, function(stream) {
  clients.push(stream);

  stream.on('end', function() {
    clients = clients.filter(function(client) {
      return client !== stream;
    })
  })
});

console.log('listening on these addresses:')
var ifaces = require('os').networkInterfaces();
Object.keys(ifaces).forEach(function(key) {
  ifaces[key].forEach(function(iface) {
    if (iface.family === 'IPv4') {
      console.log(' http://' + iface.address + ':' + PORT + '/');
    }
  })
})
