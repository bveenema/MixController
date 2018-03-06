let isAdvanced = false;

onload = function(){

  // Attach listeners to slide boxes
  let slideBoxes = document.getElementsByClassName('slide-box');
  for(let i=0; i<slideBoxes.length; i++){
    let sliderElement = slideBoxes[i].getElementsByClassName('slider')[0];
    let textboxElement = slideBoxes[i].getElementsByClassName('textbox')[0];

    sliderElement.oninput = function(){
      updateSibling(textboxElement, parseFloat(this.value, 10));
    }
    sliderElement.onchange = function(){
      updateController(this.parentNode.getAttribute('name'), parseFloat(this.value, 10));
    }
    textboxElement.onchange = function(){
      updateSibling(sliderElement, parseInt(this.value, 10));
      updateController(this.parentNode.getAttribute('name'), parseFloat(this.value, 10));
    }
  }

  // Attach listener to Advanced Expander
  let advancedExpander = document.getElementById('expander');
  advancedExpander.onclick = function(){
    console.log("Clicked Expander");
    isAdvanced = !isAdvanced;
    if(isAdvanced){
      advancedExpander.getElementsByTagName('img')[0].src = "assets/plus-box.svg";
    } else {
      advancedExpander.getElementsByTagName('img')[0].src = "assets/plus.svg";
    }
  }
}

function updateSibling(sibling,value){
  sibling.value = value;
}

function updateController(variable, value){
  console.log("Updating variable: " + variable + " to " + value);
  setTimeout(onRead(String(variable), value), 2000);
}

function onRead(variable, value){
  let elements = document.getElementsByClassName('slide-box');
  for(let i=0; i<elements.length; i++){
    let name = elements[i].getAttribute('name');
    if(name === variable){
      console.log(name);
      let element = elements[i].getElementsByTagName('span');
      console.log(element)
      element[0].innerHTML = value.toString(10);
    }
  }
}
