var drawnItems;
$(document).ready(function (){
  var map = L.map('mapid').setView([61.71029918419156, 10.86324691772461], 13);
  var currentLayer;

  L.tileLayer('https://api.mapbox.com/styles/v1/petob/ciz6y0i7m001u2ro19pxb67vd/tiles/256/{z}/{x}/{y}?access_token=pk.eyJ1IjoicGV0b2IiLCJhIjoiY2l6NnhwODdvMDAwMDJxa3kzN3M3bmJ0MCJ9.clU5Cwy8LbD9rqPv4VgC7Q', {
    attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://mapbox.com">Mapbox</a>',
    maxZoom: 18,
  }).addTo(map);

  // Initialize the FeatureGroup to store editable layers
  drawnItems = new L.FeatureGroup();
  map.addLayer(drawnItems);

  // Initialize the draw control and pass it the FeatureGroup of editable layers
  var drawControl = new L.Control.Draw({
    edit: {
      featureGroup: drawnItems
    }
    });
  map.addControl(drawControl);
  map.on(L.Draw.Event.CREATED, function (e) {
   var type = e.layerType;
   var layer = e.layer;
   if (type === 'marker') {
       // Do marker specific actions
   }
   // Do whatever else you need to. (save to db; add to map etc)
   drawnItems.addLayer(layer);
   currentLayer = layer;
  });

  map.on(L.Draw.Event.DRAWSTART, function(e){
    clearLayers();
  });
});

function clearLayers(){
  drawnItems.clearLayers();
}

function save(){
  var data = drawnItems.toGeoJSON();
  $.ajax({
  type: "POST",
  url: "http://localhost:8080/api/map",
  data: data,
  success: function(data){
    var iframe = document.createElement("iframe");
    iframe.setAttribute("src", data.url);
    iframe.setAttribute("style", "display: none");
    document.body.appendChild(iframe);
  },
  error: function(){
  }
});
}
