/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dto;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author homya
 */
@Entity
@Table(name = "AUTO")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Auto.findAll", query = "SELECT a FROM Auto a")
    , @NamedQuery(name = "Auto.findByIdA", query = "SELECT a FROM Auto a WHERE a.idA = :idA")
    , @NamedQuery(name = "Auto.findByModelA", query = "SELECT a FROM Auto a WHERE a.modelA = :modelA")
    , @NamedQuery(name = "Auto.findByZnackaA", query = "SELECT a FROM Auto a WHERE a.znackaA = :znackaA")})
public class Auto implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "ID_A")
    private Integer idA;
    @Size(max = 255)
    @Column(name = "ZNACKA_A")
    private String znackaA;
    @Size(max = 255)
    @Column(name = "MODEL_A")
    private String modelA;
    @OneToMany(mappedBy = "idA", fetch = FetchType.EAGER)
    private List<Oprava> opravaList;

    public Auto() {
    }

    public Auto(Integer idA) {
        this.idA = idA;
    }

    public Integer getIdA() {
        return idA;
    }

    public void setIdA(Integer idA) {
        this.idA = idA;
    }

    public String getModelA() {
        return modelA;
    }

    public void setModelA(String modelA) {
        this.modelA = modelA;
    }

    public String getZnackaA() {
        return znackaA;
    }

    public void setZnackaA(String znackaA) {
        this.znackaA = znackaA;
    }

    @XmlTransient
    public List<Oprava> getOpravaList() {
        return opravaList;
    }

    public void setOpravaList(List<Oprava> opravaList) {
        this.opravaList = opravaList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idA != null ? idA.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Auto)) {
            return false;
        }
        Auto other = (Auto) object;
        if ((this.idA == null && other.idA != null) || (this.idA != null && !this.idA.equals(other.idA))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "db.Auto[ idA=" + idA + " ]";
    }

}
