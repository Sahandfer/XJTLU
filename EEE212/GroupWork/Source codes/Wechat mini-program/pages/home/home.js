Page({
  data: {
    opening: true,
    showContent: false, 
    disabled: false,
    updating: false,
    selectedLight: null,
    lightStatus: ['off', 'off', 'off', 'closed'], 
    disabled: false
  },

  changeStatus(){
    var lightStatus= this.data.lightStatus
    var selectedLight= this.data.selectedLight
    if (lightStatus[selectedLight - 1] == "on"){
      lightStatus[selectedLight - 1] = "off"
    }
    else{
      lightStatus[selectedLight - 1] = "on"
    }
    this.setData({
      lightStatus: lightStatus
    })
    console.log(this.data.lightStatus)
    this.setLightData()
  }
  ,
  changeLight(e){
    let lightNum = e.currentTarget.dataset.lightnum
    if (lightNum== this.data.selectedLight){
      lightNum=null;
    }
    this.setData({
      selectedLight: parseInt(lightNum)
    })
  }
  ,
  getLightData(){
    var that = this;
    if (this.data.opening){
      wx.showLoading({
        title: 'Downloading',
      })
    }
    
   if(!this.data.updating){
     wx.request({
       url: 'https://eeearduino.000webhostapp.com/lightGetter.php',
       date: {

       },
       success(res) {
         console.log("Success!")
         wx.hideLoading()
         console.log(res.data)
         that.setData({
           lightStatus: res.data.split(" "),
           showContent: true,
           opening: false
         })
       }
     })
   }
  }
  ,
  setLightData(){
    var that = this;
    var selectedLight= this.data.selectedLight
    var lightStatus= this.data.lightStatus
    this.setData({
      disabled: true, 
      updating: true
    })
    wx.showLoading({
      title: 'Updating',
    })
    wx.request({
      url: 'https://eeearduino.000webhostapp.com/lightSetter.php',
      data: {
        lightNum: "light"+selectedLight,
        status: lightStatus[selectedLight - 1]
      },
      success(res) {
        console.log("Success!")
        wx.showToast({
          title: 'Success',
          icon: 'success',
          duration: 1000
        })
        that.setData({
          disabled: false,
          updating: false
        })
        console.log(res.data)
      }
    })
  },
  onShow: function (options) {
    this.getLightData()
    setInterval(this.getLightData, 2000);
  }
})