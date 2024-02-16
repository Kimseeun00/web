const imageURL = "https://picsum.photos/1280/720";

async function setRenderBackground() {
  const response = await axios.get(imageURL, { responseType: "blob" });
  const body = document.querySelector("body");
  body.style.backgroundImage = `url(${URL.createObjectURL(response.data)})`;
}

function setTime() {
    const timer = document.querySelector(".timer");
    setInterval(() => {
      const date = new Date();
      timer.textContent = `${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`;
    }, 1000);
}

setRenderBackground();
setTime();
setInterval(() => {
  setRenderBackground();
}, 5000);