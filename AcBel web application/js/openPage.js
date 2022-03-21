function openPage(page) {
    // Hide all elements with class="tabcontent" by default */
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
      tabcontent[i].style.display = "none";
    }
  
    // Show the specific tab content
    // console.log(document.getElementsByClassName('2D_PageOpen')[0]);
    document.getElementById(page).style.display = "flex";
}

document.getElementsByClassName('2D_PageOpen')[0].addEventListener('click', function(){openPage('2D')});
document.getElementsByClassName('3D_PageOpen')[0].addEventListener('click', function(){openPage('3D')});
document.getElementsByClassName('Tree_PageOpen')[0].addEventListener('click', function(){openPage('Tree')});


// Get the element with id="defaultOpen" and click on it
document.getElementById("default_PageOpen").click();