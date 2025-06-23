let angle = 0;

function rotateImage() {
  const image = document.getElementById('rotating-image');
  angle = (angle + 1);
  image.style.transform = `rotateY(${angle}deg)`;
  requestAnimationFrame(rotateImage);
}

rotateImage();
