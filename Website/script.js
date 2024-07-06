document.addEventListener('DOMContentLoaded', function() {
    const RickButton = document.querySelector("#free-money");
    const RickImage = document.querySelector("#rickroll");

    RickButton.addEventListener("click", () => {
        RickImage.hidden = !RickImage.hidden;
    });
});
