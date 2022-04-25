function light_control(command) {
    var url = "https://api.particle.io/v1/devices/e00fce68413956d577974ec5/LIGHT_CONTROL";
    var xhr = new XMLHttpRequest();
    xhr.open("POST", url);

    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

    xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
        console.log(xhr.status);
        console.log(xhr.responseText);
    }};

    var data = "access_token=704dc8001460694ebb3dd52dc1c33bf1aefb6548&args=" + command;

    xhr.send(data);
}