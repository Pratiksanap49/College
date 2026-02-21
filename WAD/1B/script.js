document.getElementById("regForm").addEventListener("submit", function(e) {
  e.preventDefault();

  let name = document.getElementById("name").value;
  let email = document.getElementById("email").value;
  let password = document.getElementById("password").value;

  let userData = {
    name: name,
    email: email,
    password: password
  };


  let users = JSON.parse(localStorage.getItem("users")) || [];


  let xhr = new XMLHttpRequest();
  xhr.open("POST", "dummyURL", true);
  xhr.setRequestHeader("Content-Type", "application/json");

  xhr.onload = function () {
    users.push(userData);   
    localStorage.setItem("users", JSON.stringify(users));

   
    window.open("list.html", "_blank");
  };

  xhr.send(JSON.stringify(userData));
});


