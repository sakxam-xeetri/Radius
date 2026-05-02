document.addEventListener("DOMContentLoaded", () => {
    fetchStatus();
    setInterval(fetchStatus, 3000);
});

function fetchStatus() {
    fetch('/api/status')
        .then(res => res.json())
        .then(data => {
            const statusText = document.getElementById('status-text');
            const statusDot = document.getElementById('status-dot');
            const visualizer = document.getElementById('visualizer');
            const volInput = document.getElementById('volume');
            const volLabel = document.getElementById('vol-val');

            if (data.playing) {
                statusText.innerText = data.url;
                statusDot.classList.add('playing');
                visualizer.classList.add('active');
            } else {
                statusText.innerText = 'Stopped';
                statusDot.classList.remove('playing');
                visualizer.classList.remove('active');
            }
            
            // Only update if not actively sliding
            if (document.activeElement !== volInput) {
                volInput.value = data.volume;
                volLabel.innerText = data.volume;
            }
        })
        .catch(err => {
            document.getElementById('status-text').innerText = 'Device Offline / Error';
            document.getElementById('status-dot').classList.remove('playing');
            document.getElementById('visualizer').classList.remove('active');
        });
}

function playPreset(url) {
    playStream(url);
}

function playCustom() {
    const url = document.getElementById('custom-url').value;
    if(url) {
        playStream(url);
    }
}

function playStream(url) {
    document.getElementById('status-text').innerText = 'Buffering...';
    fetch('/api/play', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `url=${encodeURIComponent(url)}`
    })
    .then(res => res.json())
    .then(() => fetchStatus());
}

function stopStream() {
    fetch('/api/stop', { method: 'POST' })
    .then(res => res.json())
    .then(() => fetchStatus());
}

function setVolume(level) {
    fetch('/api/volume', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `level=${level}`
    });
}
