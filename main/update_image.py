# sudo apt install python3 python3-pip wkhtmltopdf
# pip3 install Pillow imgkit
import imgkit
from PIL import Image
import PIL
import os
import glob
options = {
    'width': '1080',
    'height': '1080'
}
imgkit.from_url('clementplanque.fr', './images/clementplanque.jpg', options=options)
imgkit.from_url('https://ticket-demo.pandeo.fr', './images/ticket.jpg', options=options)
imgkit.from_url('https://monitoring-demo.pandeo.fr/', './images/monitoring.jpg', options=options)
imgkit.from_url('https://www.42lyon.fr/', './images/piscine.jpg', options=options)
image = Image.open('./images/clementplanque.jpg')
image = image.convert('RGB')
image.save('./images/clementplanque.webp', 'webp')
image = Image.open('./images/ticket.jpg')
image = image.convert('RGB')
image.save('./images/ticket.webp', 'webp')
image = Image.open('./images/monitoring.jpg')
image = image.convert('RGB')
image.save('./images/monitoring.webp', 'webp')
image = Image.open('./images/piscine.jpg')
image = image.convert('RGB')
image.save('./images/piscine.webp', 'webp')
os.remove("./images/clementplanque.jpg")
os.remove("./images/ticket.jpg")
os.remove("./images/monitoring.jpg") 
os.remove("./images/piscine.jpg") 