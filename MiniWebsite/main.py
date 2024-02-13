from flask import Flask, render_template, redirect, url_for, request
from flask_bootstrap import Bootstrap5
from flask_sqlalchemy import SQLAlchemy
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired, URL
from flask_ckeditor import CKEditor, CKEditorField
from datetime import date
import smtplib
import requests

# USE YOUR OWN point LINK! ADD AN IMAGE URL FOR YOUR POST. 👇
posts = requests.get("https://api.npoint.io/a5bb28c611dd2b393488").json()
OWN_EMAIL = "YOUR OWN EMAIL ADDRESS"
OWN_PASSWORD = "YOUR EMAIL ADDRESS PASSWORD"

app = Flask(__name__)
app.config['SECRET_KEY'] = '8BYkEfBA6O6donzWlSihBXox7C0sKR6b'
Bootstrap5(app)

# CONNECT TO DB
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///posts.db'
db = SQLAlchemy()
db.init_app(app)

ckeditor = CKEditor(app)

# CONFIGURE TABLE
class BlogPost(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(250), unique=True, nullable=False)
    subtitle = db.Column(db.String(250), nullable=False)
    date = db.Column(db.String(250), nullable=False)
    body = db.Column(db.Text, nullable=False)
    author = db.Column(db.String(250), nullable=False)
    img_url = db.Column(db.String(250), nullable=False)

class PostForm(FlaskForm):
    title = StringField('Blog Post Title', validators=[DataRequired()])
    subtitle = StringField('Subtitle', validators=[DataRequired()])
    author = StringField('Your Name', validators=[DataRequired()])
    img_url = StringField('Blog Image URL', validators=[DataRequired(), URL()])
    blog_content = CKEditorField('Blog Content', validators=[DataRequired()]) 
    submit = SubmitField('Submit Post')

with app.app_context():
    db.create_all()

@app.route('/')
def get_all_posts():
    posts = db.session.execute(db.select(BlogPost)).scalars().all()
    return render_template("index.html", all_posts=posts)

@app.route('/post/<int:post_id>')
def show_post(post_id):
    requested_post = db.get_or_404(BlogPost, post_id)
    return render_template("post.html", post=requested_post)

@app.route('/new-post', methods=["POST", "GET"])
def add_new_post():
    form = PostForm()
    if request.method == "POST":
        new_blog = BlogPost(
            title=form.title.data,
            subtitle=form.subtitle.data,
            body=form.blog_content.data,
            img_url=form.img_url.data,
            author=form.author.data,
            date=date.today().strftime("%B %d, %Y")
        )
        db.session.add(new_blog)
        db.session.commit()
        
        return redirect(url_for("get_all_posts"))
    
    title = "New Post"
    return render_template("make-post.html", form=form, h1=title)

@app.route("/edit-post/<post_id>", methods=["GET", "POST"])
def edit_post(post_id):
    post = db.get_or_404(BlogPost, post_id)
    edit_form = PostForm(
        title=post.title,
        subtitle=post.subtitle,
        img_url=post.img_url,
        author=post.author,
        blog_content=post.body
    )

    if edit_form.validate_on_submit():
        post.title=edit_form.title.data
        post.subtitle=edit_form.subtitle.data
        post.body=edit_form.blog_content.data
        post.img_url=edit_form.img_url.data
        post.author=edit_form.author.data
        post.date=date.today().strftime("%B %d, %Y")
        db.session.commit()
        return redirect(url_for("show_post", post_id=post.id))

    title = "Edit Post"
    return render_template("make-post.html", form=edit_form, h1=title) 

@app.route("/delete/<post_id>")
def delete_post(post_id):
    post = db.get_or_404(BlogPost, post_id)
    db.session.delete(post)
    db.session.commit()
    return redirect(url_for("get_all_posts"))

@app.route("/about")
def about():
    return render_template("about.html")

@app.route("/contact", methods=["POST", "GET"])
def contact():
    if request.method == "GET":
        return render_template("contact.html")
    elif request.method == "POST":
        if request.method == "POST":
            data = request.form
            data = request.form
            send_email(data["name"], data["email"], data["phone"], data["message"])
            return render_template("contact.html", msg_sent=True)
        
def send_email(name, email, phone, message):
    email_message = f"Subject:New Message\n\nName: {name}\nEmail: {email}\nPhone: {phone}\nMessage:{message}"
    with smtplib.SMTP("smtp.gmail.com") as connection:
        connection.starttls()
        connection.login(OWN_EMAIL, OWN_PASSWORD)
        connection.sendmail(OWN_EMAIL, OWN_EMAIL, email_message)

if __name__ == "__main__":
    app.run(debug=True, port=5003)
