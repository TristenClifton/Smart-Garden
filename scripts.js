var particle = new Particle();

//This is not considered secure if exposed to the web, local use is fine
const accessToken = '1eae8755bac11dcea2cddbc2dca6344da5937c1c';
const deviceId = 'BlueNugget';

const times = [
    "monStart",
    "monFinish",
    "tueStart",
    "tueFinish",
    "wedStart",
    "wedFinish",
    "thuStart",
    "thuFinish",
    "friStart",
    "friFinish",
    "satStart",
    "satFinish",
    "sunStart",
    "sunFinish"
];

var timeValues = [];

function UpdateValue(time, index) {
    document.getElementById("statusSpan1").innerHTML = 'Loading Times';
    particle.getVariable({
        deviceId: deviceId,
        name: time,
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById(time).value = data.body.result;
            timeValues[index] = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
}

function FetchVaribles() {
    particle.getVariable({
        deviceId: deviceId,
        name: "temprature",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("tempratureValue").innerHTML = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
    particle.getVariable({
        deviceId: deviceId,
        name: "moisture",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("moistureValue").innerHTML = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
    particle.getVariable({
        deviceId: deviceId,
        name: "lux",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("luxValue").innerHTML = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
}

function FetchOverides() {
    particle.getVariable({
        deviceId: deviceId,
        name: "autoStartEnabled",
        auth: accessToken
    }).then(
        function(data) {
            if (data.body.result == true) {
                document.getElementById("autoStartEnabled").checked = true;
            } else {
                document.getElementById("autoStartEnabled").checked = false;
            }

        },
        function(err) {
            console.log("An error occurred:", err);
        });
    particle.getVariable({
        deviceId: deviceId,
        name: "autoTemp",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("autoTemp").value = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
    particle.getVariable({
        deviceId: deviceId,
        name: "autoMoist",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("autoMoist").value = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
    particle.getVariable({
        deviceId: deviceId,
        name: "autoLux",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("autoLux").value = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
    particle.getVariable({
        deviceId: deviceId,
        name: "autoDuration",
        auth: accessToken
    }).then(
        function(data) {
            document.getElementById("autoDuration").value = data.body.result;
        },
        function(err) {
            console.log("An error occurred:", err);
        });
}


function FillTable() {
    particle.getVariable({
        deviceId: deviceId,
        name: "running",
        auth: accessToken
    }).then(
        function(data) {
            if (data.body.result == true) {
                document.getElementById("running").innerHTML = "Yes";
            } else {
                document.getElementById("running").innerHTML = "No";
            }
        },
        function(err) {
            console.log("An error occurred:", err);
        });

    while (true) {
        timeValues = []
        for (i = 0; i < times.length; i++) {
            timeValues.pop("00:00");
        }

        for (i = 0; i < times.length; i++) {
            UpdateValue(times[i], i);
        }

        var Loaded = true
        for (i = 0; i < times.length; i++) {
            if (times[i] == "") {
                Loaded = false
            }
        }
        if (Loaded) {
            break;
        }
    }
    FetchVaribles();
    FetchOverides();
    document.getElementById("statusSpan1").innerHTML = "Loaded Succesfully";
}

function UpdateTimeTable() {

    var changed = false;

    for (i = 0; i < times.length; i++) {
        if (timeValues[i] != document.getElementById(times[i]).value) {

            changed = true;
            document.getElementById("statusSpan2").innerHTML = timeValues;
            document.getElementById("statusSpan3").innerHTML = document.getElementById(times[i]).value;

            setTimeout(function() {}, 5000);

            startOrfinish = 0

            if (times[i].substring(3, 8) == "Start") {
                startOrfinish = 1
            }

            cmd = times[i].substring(0, 3) + startOrfinish + document.getElementById(times[i]).value;
            document.getElementById("statusSpan3").innerHTML = cmd;

            particle.callFunction({ deviceId, name: 'UpdateTimes', argument: cmd, auth: accessToken }).then(
                function(data) {
                    //reports to user if command worked correctly.
                    document.getElementById("statusSpan1").innerHTML = 'Call completed';
                },
                function(err) {
                    //reports to user if command failed and supplys them with the error
                    document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
                }
            );

        }
    }
    if (!changed) {
        document.getElementById("statusSpan1").innerHTML = "Nothing To change";
    }
}



function updateTimes(cmd) {
    // Gets the status to nothing
    document.getElementById("statusSpan").innerHTML = '';
    // Used to switch between leds using Particle.function "ledFunction"
    particle.callFunction({
        deviceId,
        name: 'ledFunction',
        argument: cmd,
        auth: accessToken
    }).then(
        function(data) {
            //reports to user if command worked correctly.
            document.getElementById("statusSpan").innerHTML = 'Call completed';
        },
        function(err) {
            //reports to user if command failed and supplys them with the error
            document.getElementById("statusSpan").innerHTML = 'Error calling device: ' + err;
        }
    );
}

function UpdateAutoStart() {
    document.getElementById("statusSpan1").innerHTML = 'updating';

    if (document.getElementById("autoStartEnabled").checked == true) {
        particle.callFunction({ deviceId, name: 'UpdateAutoStartEnabled', argument: "true", auth: accessToken }).then(
            function(data) {
                //reports to user if command worked correctly.
                document.getElementById("statusSpan1").innerHTML = 'Call completed';
            },
            function(err) {
                //reports to user if command failed and supplys them with the error
                document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
            }
        );
    } else {
        particle.callFunction({ deviceId, name: 'UpdateAutoStartEnabled', argument: "false", auth: accessToken }).then(
            function(data) {
                //reports to user if command worked correctly.
                document.getElementById("statusSpan1").innerHTML = 'Call completed';
            },
            function(err) {
                //reports to user if command failed and supplys them with the error
                document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
            }
        );
    }
    particle.callFunction({ deviceId, name: 'UpdateAutoTemp', argument: document.getElementById("autoTemp").value.toString(), auth: accessToken }).then(
        function(data) {
            //reports to user if command worked correctly.
            document.getElementById("statusSpan1").innerHTML = 'Call completed';
        },
        function(err) {
            //reports to user if command failed and supplys them with the error
            document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
        }
    );
    particle.callFunction({ deviceId, name: 'UpdateAutoMoist', argument: document.getElementById("autoMoist").value.toString(), auth: accessToken }).then(
        function(data) {
            //reports to user if command worked correctly.
            document.getElementById("statusSpan1").innerHTML = 'Call completed';
        },
        function(err) {
            //reports to user if command failed and supplys them with the error
            document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
        }
    );
    particle.callFunction({ deviceId, name: 'UpdateAutoLux', argument: document.getElementById("autoLux").value.toString(), auth: accessToken }).then(
        function(data) {
            //reports to user if command worked correctly.
            document.getElementById("statusSpan1").innerHTML = 'Call completed';
        },
        function(err) {
            //reports to user if command failed and supplys them with the error
            document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
        }
    );
    particle.callFunction({ deviceId, name: 'UpdateAutoDuration', argument: document.getElementById("autoDuration").value.toString(), auth: accessToken }).then(
        function(data) {
            //reports to user if command worked correctly.
            document.getElementById("statusSpan1").innerHTML = 'Call completed';
        },
        function(err) {
            //reports to user if command failed and supplys them with the error
            document.getElementById("statusSpan1").innerHTML = 'Error calling device: ' + err;
        }
    );
    document.getElementById("updated").innerHTML = 'updating';
}

function webFunction() {
    particle.getVariable({
        deviceId: deviceId,
        name: "monStart",
        auth: accessToken
    }).then(
        function(data) {
            //var timeControl = document.querySelector('input[type="time"]');
            //timeControl.value = '15:30';

            // add code to do something with value returned as: data.body.result
            document.getElementById("varibleOut").innerHTML = data.body.result;

        },
        function(err) {
            console.log("An error occurred:", err);
        });
}