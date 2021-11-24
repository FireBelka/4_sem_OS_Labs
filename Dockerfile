FROM nginx
RUN touch /usr/share/nginx/html/index.html
COPY README.md > /usr/share/nginx/html/index.html
EXPOSE 80
EXPOSE 443
