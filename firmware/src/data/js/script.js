var DEBUG = 0;

// CLIENT -> SERVER
// R - Request status
// H - Home steppers
// M[0-3] - Set mode [OFF,MAN,AUT,EXT]
// L[0-255] - Set laser intensity
// P[1-20] - Set preset (applicable when M1)
// S[1-2] - Set scaling (applicable when M1)
// V[1-3] - Set speed (applicable when M1)
// C0[0-Xmax,0-Ymax,0-1] - External control [X,Y,Laser]
// C1[0-Xmax,0-Ymax] - External control [X,Y]
// C2[0-1] - External control [Laser On, Laser Off]

// SERVER -> CLIENT
// M[0-3] - Mode [OFF,MAN,AUT,EXT]
// L[0-255] - Laser intensity
// P[1-20] - Preset (used when M1)
// S[1-2] - Scaling (used when M1)
// V[1-3] - Speed (used when M1)
// C0[0-Xmax,0-Ymax,0-1] - Current position, laser [X,Y,Laser]

const MSG_STATUS = "R";
const MSG_HOME = "H";
const MSG_MODE = "M";
const MSG_LASER = "L";
const MSG_PRESET = "P";
const MSG_SCALING = "S";
const MSG_SPEED = "V";
const MSG_CTR = "C0";
const MSG_CTR_XY = "C1";
const MSG_CTR_LAS = "C2";
const MSG_FW_VER = "Z";

const eventTimeout = 20; // [ms] time between slider and canvas event retriggers
var lastEvent = new Date();
var btnsPreset = document.getElementsByClassName("btn_preset");
var btnsScaling = document.getElementsByClassName("btn_scaling");
var btnsSpeed = document.getElementsByClassName("btn_speed");

var connection;
if (DEBUG==1) connection = new WebSocket("wss://demo.piesocket.com/v3/channel_123?api_key=VCXCEuvhGcBDP7XhiJJUDvR1e1D3eiVjgZ9VRiaV&notify_self");
else connection = new WebSocket('ws://' + location.hostname + "/ws");

connection.onopen = function () {
  connection.send(MSG_STATUS + ";" + MSG_FW_VER); // send request for status packet and FW version
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  if (DEBUG==1) console.log('Server: ', e.data);
  console.log('Server: ', e.data);
  e.data.split(';').forEach(msg => processMessage(msg));
};
connection.onclose = function(){
  console.log('WebSocket connection closed');
};

var canvas = document.getElementById('manual_canvas');
var ctx = canvas.getContext("2d");
var canvas_flag = false;
const canvas_x_max = canvas.width;
const canvas_y_max = canvas.height;
const canvas_scale = 50/300;
writeAxis();

canvas.addEventListener("mousemove", function (e) {
  findxy('move', e)
}, false);
canvas.addEventListener("mousedown", function (e) {
  findxy('down', e)
}, false);
canvas.addEventListener("mouseup", function (e) {
  findxy('up', e)
}, false);
canvas.addEventListener("mouseout", function (e) {
  findxy('out', e)
}, false);

function findxy(res, e) {
  if (res == 'down') {
    canvas_flag = true;
    connection.send(MSG_CTR_LAS + '1' + ';');
  }
  if (res == 'up' || res == "out") {
    canvas_flag = false;
	connection.send(MSG_CTR_LAS + '0' + ';');
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    writeAxis();
  }
  if (res == 'move' || res == 'down') {
    if (canvas_flag) {
	  if (new Date() - lastEvent < eventTimeout) return;
      var mousePos = getMousePos(canvas, e);
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      ctx.beginPath();
      ctx.arc(mousePos.x, mousePos.y, 5, 0, 2 * Math.PI);
      ctx.fillStyle = '#00FF88';
      ctx.fill();
      ctx.lineWidth = 1;
      ctx.strokeStyle = 'black';
      ctx.stroke();
      ctx.closePath();
      var x = mousePos.x;
      var y = mousePos.y;
      x = x < 0 ? 0 : x > canvas_x_max ? canvas_x_max : x;
      y = y < 0 ? 0 : y > canvas_y_max ? canvas_y_max : y;
      x = Math.round(x*canvas_scale);
      y = Math.round(y*canvas_scale);
	  connection.send(MSG_CTR_XY + x + "," + y + ';');
      writeAxis();
      writeMessage(canvas, x + '\t' + y);
	  lastEvent = new Date();
    }
  }
}

function writeMessage(canvas, message) {
  ctx.font = '18pt Calibri';
  ctx.fillStyle = 'white';
  ctx.textAlign = "center";
  ctx.fillText(message, canvas_x_max/2, canvas_y_max/2);
}

function writeAxis() {
  ctx.font = '18pt Calibri';
  ctx.fillStyle = 'white';
  ctx.textAlign = "center";
  ctx.fillText(canvas_x_max*canvas_scale, canvas_x_max/2, canvas_y_max-10);
  ctx.save();
  ctx.translate(0,canvas_y_max);
  ctx.rotate(-0.5*Math.PI);
  ctx.textAlign = "center";
  ctx.fillText(canvas_y_max*canvas_scale, canvas_y_max/2, canvas_x_max-10);
  ctx.restore();
}

function getMousePos(canvas, evt) {
  var rect = canvas.getBoundingClientRect();
  return {
    x: evt.clientX - rect.left,
    y: evt.clientY - rect.top
  };
}

var btnsHandle = document.getElementsByClassName("btn_handle");
for (var i = 0; i < btnsHandle.length; i++) {
  btnsHandle[i].addEventListener("click", event => {
	var id = (event.target.id != "") ? event.target.id : event.target.parentNode.id;
    handleButton(id);
  });
}

for (var i = 0; i < btnsPreset.length; i++) {
  btnsPreset[i].innerHTML="<img src='img/presets/" + btnsPreset[i].id + ".png'>";
}

function sendLaserIntensity() {
  if (new Date() - lastEvent < eventTimeout) return;
  var laser_intensity = document.getElementById('laser_intensity').value;
  connection.send(MSG_LASER + laser_intensity + ";");
  lastEvent = new Date();
}

function handleButton(par){
  connection.send(par + ';');
}

function processMessage(data) {
  var id = data.charAt(0);
  var substr = data.substring(1)
  var val = parseInt(substr);

  if (id == MSG_MODE) {
	var btnList = document.getElementsByClassName("btn_mode");
	for (var i = 0; i < btnList.length; i++) {
		btnList[i].classList.remove("active");
	}
    document.getElementById("M" + val).className += " active";
    if (val == 0 || val == 2) {
	  document.getElementById('section-mode-manual').style.display = 'none';
      document.getElementById('section-mode-external').style.display = 'none';
    }
    else if (val == 1) {
      document.getElementById('section-mode-manual').style.display = 'block';
      document.getElementById('section-mode-external').style.display = 'none';
    }
	else if (val == 3) {
      document.getElementById('section-mode-manual').style.display = 'none';
      document.getElementById('section-mode-external').style.display = 'block';
    }		
  }
  else if (id == MSG_LASER) {
    document.getElementById("laser_intensity").value = val;
  }
  else if (id == MSG_PRESET) {
    for (var i = 0; i < btnsPreset.length; i++) {
      btnsPreset[i].classList.remove("active");
    }
    document.getElementById("P" + val).className += " active";
  }
  else if (id == MSG_SCALING) {
    for (var i = 0; i < btnsScaling.length; i++) {
      btnsScaling[i].classList.remove("active");
    }
    document.getElementById("S" + val).className += " active";
  }
  else if (id == MSG_SPEED) {
    for (var i = 0; i < btnsSpeed.length; i++) {
      btnsSpeed[i].classList.remove("active");
    }
    document.getElementById("V" + val).className += " active";
  }
  else if (id == MSG_CTR) {
	var xyl = substr.split(',');
	console.log("X: " + xyl[0] + " Y: " + xyl[1] + " L: " + xyl[2]);
  }
  else if (id == MSG_CTR_XY) {
	var xyl = substr.split(',');
	console.log("X: " + xyl[0] + " Y: " + xyl[1] + " L: " + xyl[2]);
  }
  else if (id == MSG_CTR_LAS) {
    var xyl = substr.split(',');
	console.log("X: " + xyl[0] + " Y: " + xyl[1] + " L: " + xyl[2]);
  }
  else if (id == MSG_FW_VER) {
	document.getElementById("fw-ver").innerHTML = "FW VER " + substr;
  }
}