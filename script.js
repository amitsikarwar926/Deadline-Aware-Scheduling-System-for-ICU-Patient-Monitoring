const tasks = [
    { name: "ECG", deadline: 1000 },
    { name: "SpO2", deadline: 1500 },
    { name: "BP", deadline: 2000 },
    { name: "TEMP", deadline: 2500 }
];

function randomDelay() {
    return Math.floor(Math.random() * 3000);
}

function scheduler() {
    tasks.sort((a, b) => a.deadline - b.deadline);
    tasks.forEach(task => executeTask(task));
}

function executeTask(task) {
    const start = performance.now();
    const delay = randomDelay();

    setTimeout(() => {
        const execTime = performance.now() - start;
        const status = execTime <= task.deadline ? "OK" : "MISS";
        updateUI(task.name, status);
    }, delay);
}

function updateUI(sensor, status) {
    if (sensor === "ECG") {
        document.getElementById("ecgVal").innerText =
            Math.floor(60 + Math.random() * 40);
        setStatus("ecgStatus", status);
    }

    if (sensor === "SpO2") {
        document.getElementById("spo2Val").innerText =
            Math.floor(94 + Math.random() * 6);
        setStatus("spo2Status", status);
    }

    if (sensor === "BP") {
        document.getElementById("bpVal").innerText =
            (110 + Math.floor(Math.random() * 20)) + "/" +
            (70 + Math.floor(Math.random() * 10));
        setStatus("bpStatus", status);
    }

    if (sensor === "TEMP") {
        document.getElementById("tempVal").innerText =
            (36 + Math.random()).toFixed(1);
        setStatus("tempStatus", status);
    }
}

function setStatus(id, status) {
    const el = document.getElementById(id);
    if (status === "OK") {
        el.innerText = "Processed Within Deadline";
        el.className = "status ok";
    } else {
        el.innerText = "Deadline Missed";
        el.className = "status miss";
    }
}

setInterval(scheduler, 4000);
