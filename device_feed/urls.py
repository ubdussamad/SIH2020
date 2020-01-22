from django.urls import path
from django.conf.urls import url
from . import views

urlpatterns = [
    path('', views.home, name='device_feed-home'),
    path('login/', views.login, name='device_feed-login'),
    # path('output/', views.auth),
    url(r'^login/output/$',views.auth),
]
