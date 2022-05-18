function openPage(page) {
    var i, tabcontent;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
      // tabcontent[i].style.display = "none";
      tabcontent[i].style.visibility = "hidden";
    }

    // document.getElementById(page).style.display = "flex";
    document.getElementById(page).style.visibility = "visible";
}

document.getElementsByClassName('2D_PageOpen')[0].addEventListener('click', function(){openPage('2D')});
document.getElementsByClassName('3D_PageOpen')[0].addEventListener('click', function(){openPage('3D')});
document.getElementsByClassName('Tree_PageOpen')[0].addEventListener('click', function(){openPage('Tree')});

// Get the element with id="defaultOpen" and click on it
document.getElementById("default_PageOpen").click();