const firebaseConfig = {
    // Your Firebase configuration here
    apiKey: "AIzaSyBt8nRZY166Ql7Xz0syEWqqQOgv7xHgaPo",
    authDomain: "transform-auto.firebaseapp.com",
    databaseURL: "https://transform-auto-default-rtdb.firebaseio.com",
    projectId: "transform-auto",
    storageBucket: "transform-auto.appspot.com",
    messagingSenderId: "634131483595",
    appId: "1:634131483595:web:2d621e1a91344f41b1844e",
    measurementId: "G-GZ57FN7QDJ"
  };
  firebase.initializeApp(firebaseConfig);

  $(document).ready(function(){
    var database = firebase.database();
    var MotorStatus;

    database.ref().on("value", function(snap){
      MotorStatus = snap.val().MotorStatus;
      if (MotorStatus == "1") {
        document.getElementById("unact").style.display = "none";
        document.getElementById("act").style.display = "block";
      } else {
        document.getElementById("unact").style.display = "block";
        document.getElementById("act").style.display = "none";
      }
    });

    $(".toggle-btn").click(function(){
      var firebaseRef = firebase.database().ref().child("MotorStatus");

      if (MotorStatus == 1) {
        firebaseRef.set(0); // Send integer value 0
        MotorStatus = 0;
      } else {
        firebaseRef.set(1); // Send integer value 1
        MotorStatus = 1;
      }
    });
  });